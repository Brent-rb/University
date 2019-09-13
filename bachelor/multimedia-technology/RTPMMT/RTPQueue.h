#pragma once
#include <queue>
#include <jrtplib3/rtppacket.h>
#include "RTPCompare.h"

class RTPQueue
{
public:
	RTPQueue();
	~RTPQueue();

	void push(jrtplib::RTPPacket* packet);
	jrtplib::RTPPacket* pop();

	int getSize();

private:
	std::priority_queue <jrtplib::RTPPacket*, std::vector<jrtplib::RTPPacket*>, RTPCompare> $queue;
};

