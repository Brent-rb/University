#pragma once
#include <jrtplib3/rtppacket.h>

class RTPCompare
{
public:
	bool operator() (jrtplib::RTPPacket* left, jrtplib::RTPPacket* right);
};

