#pragma once
#include <stdint.h>
#include "jrtplib3/rtpsession.h"
#include "jrtplib3/rtpudpv4transmitter.h"
#include "jrtplib3/rtpipv4address.h"
#include "jrtplib3/rtpsessionparams.h"
#include "jrtplib3/rtperrors.h"
#include <jrtplib3/rtppacket.h>
#ifndef WIN32
	#include <netinet/in.h>
	#include <arpa/inet.h>
#else
	#include <winsock2.h>
#endif // WIN32
#include <thread>
#include <mutex>
#include "semaphore.h"
#include <queue>

using namespace jrtplib;

class RTPConnector
{
public:
	RTPConnector(uint16_t basePort, uint32_t targetIp, uint16_t targetPort);
	~RTPConnector();

	bool checkError(int errorNum);
	
	bool isCancelled();
	void cancel();
	void start();
	void join();

	RTPPacket* getPacket(bool blocking);
	void releasePacket(RTPPacket* packet);

private:
	void runInBackground();
	bool sendDummyPacket();
	bool pollForData();

	RTPPacket* popQueue(bool fakeWait);
	void pushQueue(RTPPacket* packet);

private:
	uint32_t $targetIp;
	uint16_t $targetPort;
	uint16_t $basePort;

	RTPSession $rtpSession;
	RTPUDPv4TransmissionParams $transParams;
	RTPSessionParams $sessionParams;

	std::thread* $thread;
	std::mutex $cancelledMutex;

	std::queue<RTPPacket*> $packetQueue;
	std::mutex $queueMutex;
	semaphore $queueSem;

	bool $cancelled;
};

