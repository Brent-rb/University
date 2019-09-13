#include "RTPConnector.h"
#include <iostream>

RTPConnector::RTPConnector(uint16_t basePort, uint32_t targetIp, uint16_t targetPort): $targetIp(targetIp), $targetPort(targetPort), $basePort(basePort), $thread(nullptr), $cancelled(false) {
	// Network order
	$targetIp = ntohl($targetIp);
	// IMPORTANT: The local timestamp unit MUST be set, otherwise
	//            RTCP Sender Report info will be calculated wrong
	// In this case, we'll be sending 10 samples each second, so we'll
	// put the timestamp unit to (1.0/10.0)
	$sessionParams.SetOwnTimestampUnit(1.0 / 10.0);
	$sessionParams.SetAcceptOwnPackets(true);
    $sessionParams.SetProbationType(jrtplib::RTPSources::NoProbation);
	$transParams.SetPortbase($basePort);
    $transParams.SetRTPReceiveBuffer(2000000);
	RTPIPv4Address ipAddr($targetIp, $targetPort);
	if (checkError($rtpSession.Create($sessionParams, &$transParams)) || checkError($rtpSession.AddDestination(ipAddr))) {
		std::cout << "Aborting...";
		exit(-1);
	}
}


RTPConnector::~RTPConnector()
{
	if ($thread != nullptr) {
		delete $thread;
	}

	RTPPacket* packet;
	while ((packet = popQueue(false)) != nullptr) {
		releasePacket(packet);
	}
}

bool RTPConnector::checkError(int errorNum)
{
	if (errorNum < 0)
	{
		std::cout << "ERROR: " << RTPGetErrorString(errorNum) << std::endl;
		return true;
	}

	return false;
}

void RTPConnector::runInBackground() {
	while(!isCancelled()) {
		bool packetSent = sendDummyPacket();
		bool dataReceived = pollForData();

        RTPTime::Wait(RTPTime(0, 1000));
	}

	$rtpSession.BYEDestroy(RTPTime(10, 0), 0, 0);
}

bool RTPConnector::sendDummyPacket() {
    //std::cout << "Sending packet." << std::endl;

	// send the packet
	int status = $rtpSession.SendPacket((void *)"1234567890", 10, 0, false, 10);
	if (checkError(status)) {
		std::cout << "Error occured when sending dummy packet." << std::endl;
		return true;
	}

	return false;
}

bool RTPConnector::pollForData() {
    //std::cout << "Getting data." << std::endl;
	$rtpSession.BeginDataAccess();

	// check incoming packets
	if ($rtpSession.GotoFirstSourceWithData()) {
		do {
			RTPPacket *pack;

			while ((pack = $rtpSession.GetNextPacket()) != NULL) {
                //std::cout << "Packet Loop" << std::endl;
                //std::cout << "SN: " << pack->GetSequenceNumber() << std::endl;
				pushQueue(pack);
			}
		} while ($rtpSession.GotoNextSourceWithData());
	}

	$rtpSession.Poll();
	$rtpSession.EndDataAccess();
	return false;
}

bool RTPConnector::isCancelled() {
	$cancelledMutex.lock();
	bool result = $cancelled;
	$cancelledMutex.unlock();

	return result;
}

void RTPConnector::cancel() {
	$cancelledMutex.lock();
	$cancelled = true;
	$cancelledMutex.unlock();
}

void RTPConnector::start() {
	if ($thread == nullptr) {
		// Create a thread.
		$thread = new std::thread(&RTPConnector::runInBackground, this);
	}
}

void RTPConnector::join() {
	if ($thread != nullptr) {
		$thread->join();
	}
}

RTPPacket* RTPConnector::getPacket(bool blocking) {
	if (blocking) {
		$queueSem.wait();
		return popQueue(false);
	}
	else {
		return popQueue(true);
	}
}

RTPPacket* RTPConnector::popQueue(bool fakeWait) {
	RTPPacket* toRet = nullptr;

	$queueMutex.lock();
	if (!$packetQueue.empty()) {
		toRet = $packetQueue.front();
		$packetQueue.pop();
		if(fakeWait)
			$queueSem.wait();
	}
	$queueMutex.unlock();

	return toRet;
}

void RTPConnector::pushQueue(RTPPacket* packet) {
	$queueMutex.lock();
	$packetQueue.push(packet);
	$queueSem.notify();
	$queueMutex.unlock();
}

void RTPConnector::releasePacket(RTPPacket* packet) {
	$rtpSession.DeletePacket(packet);
}
