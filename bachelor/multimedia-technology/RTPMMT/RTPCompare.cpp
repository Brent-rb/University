#include "RTPCompare.h"
#include <algorithm>

bool RTPCompare::operator() (jrtplib::RTPPacket* left, jrtplib::RTPPacket* right) {
	uint32_t difference = std::abs((long) right->GetTimestamp() - (long) left->GetTimestamp());
	if (difference < (UINT32_MAX / 2)) {
		if(difference != 0)
			return left->GetTimestamp() < right->GetTimestamp();
		else {
			uint16_t seqDifference = std::abs((int)right->GetSequenceNumber() - left->GetSequenceNumber());
			if (seqDifference < UINT16_MAX / 2) {
				return left->GetSequenceNumber() < right->GetSequenceNumber();
			}
			else {
				return left->GetSequenceNumber() > right->GetSequenceNumber();
			}
		}
	}
	else {
		return left->GetTimestamp() > right->GetTimestamp();
	}
}
