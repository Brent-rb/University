#include "RTPSyncer.h"
#include <iostream>
#include <algorithm>
#include <QImage>
#include <chrono>

RTPSyncer::RTPSyncer(uint16_t basePort, uint32_t targetIp, uint16_t targetPort, int delay) {
	$connector = new RTPConnector(basePort, targetIp, targetPort);
    $delay = delay;
}


RTPSyncer::~RTPSyncer() {
	delete $connector;
	
	while (!$map.empty()) {
		RTPFrame* frame = $map.begin()->second;
		deleteFrame(frame);
		delete frame;
		$map.erase($map.begin());
	}
}

void RTPSyncer::run() {
	$connector->start();
	RTPPacket* packet;

    while (!isCancelled()) {
        //std::cout << "Loop" << std::endl;
        for (int i = 0; i < 500 && !isCancelled(); i++) {
            packet = $connector->getPacket(true);
			createFrame(packet);
		}
	}

	$connector->cancel();
	$connector->join();
}

void RTPSyncer::createFrame(jrtplib::RTPPacket* packet) {
    $mapMutex.lock();
	if ($map.count(packet->GetTimestamp()) != 0) {
		RTPFrame* frame = $map[packet->GetTimestamp()];
        $mapMutex.unlock();

		if (frame->getSize() != 0) {
			uint32_t dTime = packet->GetReceiveTime().GetSeconds() - frame->getPacket(0)->GetReceiveTime().GetSeconds();
			if (dTime > 15) {
				std::cout << "Clear" << std::endl;
				deleteFrame(frame);
				frame->clear();
			}
		}
		frame->addPacket(packet);
        if(frame->isComplete())
            frameIsReady(frame);
	}
	else {
		RTPFrame* frame = new RTPFrame();
		$map[packet->GetTimestamp()] = frame;
        $mapMutex.unlock();
		frame->addPacket(packet);
	}
}

void RTPSyncer::deleteFrame(RTPFrame* frame) {
	for (int j = 0; j < frame->getSize(); j++) {
		RTPPacket* packet = frame->getPacket(j);
		$connector->releasePacket(packet);
	}
    delete frame;
}


void RTPSyncer::cancel() {
    $cancelMutex.lock();
    $cancelled = true;
    $cancelMutex.unlock();
}

bool RTPSyncer::isCancelled() {
    bool toRet;
    $cancelMutex.lock();
    toRet = $cancelled;
    $cancelMutex.unlock();
    return toRet;
}

void RTPSyncer::frameIsReady(RTPFrame *frame) {
    qDebug() << $delay;
    if($delay >= 0) {
        calculateDelayedFrameTime(frame);
    }
    else {
        calculateFakeFrameTime(frame);
    }
}

void RTPSyncer::calculateDelayedFrameTime(RTPFrame *frame) {
    double time = 1000.0 / 90000.0;
    //printf("Frame is ready.\n");

    if($firstPacket) {
        $firstPacketTime = frame->getTimestamp();
        $firstPacketPlayTime = QDateTime::currentMSecsSinceEpoch();
        qDebug() << $firstPacketPlayTime;
        $firstPacketPlayTime += $delay;
        qDebug() << $firstPacketPlayTime;
        printf("PacketTime: %ld      PlayTime: %ld\n", $firstPacketTime, $firstPacketPlayTime);
        $firstPacket = false;
        frame->setPlayTime($firstPacketPlayTime);
    }
    else {
        uint32_t theirTime = frame->getTimestamp();
        uint32_t difference;
        qint64 playTime;

        if(theirTime > $firstPacketTime) {
            difference = theirTime - $firstPacketTime;

            if(difference > UINT32_MAX /  2) {
                difference = -($firstPacketTime + (UINT32_MAX - theirTime));
                int timeDelta = difference * time;
                playTime = $firstPacketPlayTime + timeDelta;
            }
            else {
                int seconds = difference * time;
                playTime = $firstPacketPlayTime + seconds;
                $firstPacketTime = theirTime;
                $firstPacketPlayTime = playTime;
            }
        }
        else {
            difference = $firstPacketTime - theirTime;
            if(difference > UINT32_MAX / 2) {
                difference = UINT32_MAX - $firstPacketTime + theirTime;
                playTime = $firstPacketPlayTime + difference * time;
                $firstPacketPlayTime = playTime;
                $firstPacketTime = theirTime;
            }
            else {
                playTime = $firstPacketPlayTime - ((difference) * time);
            }
        }

        frame->setPlayTime(playTime);
        removeFromDictionary(frame);
        push(frame);
        frameReady();
    }
}

void RTPSyncer::calculateFakeFrameTime(RTPFrame *frame) {
    frame->setPlayTime(QDateTime::currentMSecsSinceEpoch());
    removeFromDictionary(frame);
    push(frame);
    frameReady();
}

void RTPSyncer::removeFromDictionary(RTPFrame *frame) {
    $mapMutex.lock();
    $map.erase(frame->getTimestamp());
    $mapMutex.unlock();
}

RTPFrame* RTPSyncer::peek() {
    RTPFrame* toRet;
    $readyQueueMutex.lock();
    if(!$readyQueue.empty())
        toRet = $readyQueue.top();
    else
        toRet = nullptr;
    $readyQueueMutex.unlock();
    return toRet;
}

RTPFrame* RTPSyncer::pop() {
    RTPFrame* toRet;
    $readyQueueMutex.lock();
    if(!$readyQueue.empty()) {
        toRet = $readyQueue.top();
        $readyQueue.pop();
    }
    else
        toRet = nullptr;
    $readyQueueMutex.unlock();
    return toRet;
}

void RTPSyncer::push(RTPFrame *frame) {
    $readyQueueMutex.lock();
    $readyQueue.push(frame);
    $readyQueueMutex.unlock();
}

void RTPSyncer::removeUnreadyFrames(uint32_t timestamp) {
    bool stop = false;
    qDebug() << timestamp;

    $mapMutex.lock();
    int size = $map.size() - 1;
    auto it = $map.begin();
    auto end = $map.end();

    for(int i = 0; i < size && !stop; i++) {
        //$mapMutex.lock();
        if(it == end)
            break;
        RTPFrame* first = it->second;
        it++;

        if(first->getTimestamp() < timestamp) {
            long difference = std::abs((long)timestamp - (long)first->getTimestamp());
            if(difference < UINT32_MAX / 8) {
                qDebug() << "Delete unused.";
                $map.erase(first->getTimestamp());
                deleteFrame(first);
            }
        }
        //$mapMutex.unlock();
    }
    $mapMutex.unlock();
}
