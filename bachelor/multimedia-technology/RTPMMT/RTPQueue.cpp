#include "RTPQueue.h"

RTPQueue::RTPQueue() {
}


RTPQueue::~RTPQueue() {

}

void RTPQueue::push(jrtplib::RTPPacket* packet) {
	$queue.push(packet);
}

jrtplib::RTPPacket* RTPQueue::pop() {
	jrtplib::RTPPacket* toRet = nullptr;

	if (!$queue.empty()) {
		toRet = $queue.top();
		$queue.pop();
	}

	return toRet;
}

int RTPQueue::getSize() {
	return $queue.size();
}