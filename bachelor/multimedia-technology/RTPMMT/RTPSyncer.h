#pragma once
#include "RTPConnector.h"
#include <vector>
#include "RTPFrame.h"
#include "RTPCompare.h"
#include <map>
#include <set>
#include "mainwindow.h"
#include <mutex>
#include <QObject>
#include <QImage>
#include <QtCore>
#include <semaphore.h>

namespace jrtplib {
	class RTPPacket;
}

class RTPSyncer: public QObject {
    Q_OBJECT

public:
    RTPSyncer(uint16_t basePort, uint32_t targetIp, uint16_t targetPort, int delay);
	~RTPSyncer();

    void run();

    void cancel();
    bool isCancelled();
    void deleteFrame(RTPFrame* frame);

    RTPFrame* peek();
    RTPFrame* pop();
    void push(RTPFrame* frame);
    void remove(RTPFrame* frame);

    void removeUnreadyFrames(uint32_t timestamp);

private:
    void createFrame(jrtplib::RTPPacket*);
    void frameIsReady(RTPFrame* frame);
    void calculateDelayedFrameTime(RTPFrame* frame);
    void calculateFakeFrameTime(RTPFrame* frame);

    void removeFromDictionary(RTPFrame* frame);

private:
	RTPConnector* $connector;
	std::map<uint32_t, RTPFrame*> $map;
	std::set<uint32_t> $queue;
    std::priority_queue<RTPFrame*, std::vector<RTPFrame*>, RTPFramePlayTimeComparer> $readyQueue;

    uint8_t* $lastImage = nullptr;
    QImage* $lastQImage = nullptr;

    RTPCompare $compare;

    bool $cancelled = false;
    std::mutex $cancelMutex;
    std::mutex $readyQueueMutex;
    std::mutex $mapMutex;

    bool $firstPacket = true;
    uint32_t $firstPacketTime;
    qint64 $firstPacketPlayTime;
    long $delay;

    semaphore $readyQueueSem;

signals:
    void frameReady();
};

