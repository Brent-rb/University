#pragma once
#include <jrtplib3/rtppacket.h>
#include <vector>
#include "RTPCompare.h"
#include <QImage>

class RTPFrame {
public:
	RTPFrame();
	~RTPFrame();

	void addPacket(jrtplib::RTPPacket* packet);
	void sort();
	void print();
	void clear();

	jrtplib::RTPPacket* getPacket(int index);
	jrtplib::RTPPacket* getHeader();

	int getSize();

	bool isComplete();

	uint16_t getPacketNumber();
	uint32_t getTimestamp();

    uint8_t* getRGB(int width, int height);

    void setPlayTime(qint64 time);
    qint64 const getPlayTime();

private:
	std::vector<jrtplib::RTPPacket*> $list;
	bool $sorted;
	uint32_t $timestamp;
    qint64 $playTime = 0;
	uint16_t $packetNumber;

	const int PACKETS_NEEDED = 4;
};

class RTPFrameComparer {
public:
	bool operator()(RTPFrame* left, RTPFrame* right);

private:
	RTPCompare $compare;
};

class RTPFramePlayTimeComparer {
public:
    bool operator() (RTPFrame* left, RTPFrame* right);
};
