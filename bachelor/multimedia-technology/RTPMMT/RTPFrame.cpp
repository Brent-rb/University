#include "RTPFrame.h"
#include <algorithm>
#include <iostream>
void convertYUVtoRGBA(const unsigned char *pYUVFrame, int width, int height, unsigned char *pRGBA);


RTPFrame::RTPFrame() {
	$sorted = true;
}

RTPFrame::~RTPFrame() {

}

void RTPFrame::addPacket(jrtplib::RTPPacket* packet) {
	$list.push_back(packet);
	$sorted = false;
    $timestamp = packet->GetTimestamp();
}

jrtplib::RTPPacket* RTPFrame::getPacket(int index) {
	jrtplib::RTPPacket* toRet = nullptr;
	
	if (index < getSize() && index >= 0) {
		toRet = $list[index];
	}

	return toRet;
}

jrtplib::RTPPacket* RTPFrame::getHeader() {
	if (!$sorted) {
		sort();
	}

	return getPacket(0);
}

int RTPFrame::getSize() {
	return $list.size();
}

bool RTPFrame::isComplete() {
	if (getSize() == 4) {
		if (!$sorted)
			sort();
		
		bool startFound = false;
		bool midCorrect = true;
		bool endFound = false;
		jrtplib::RTPPacket* packet;
		uint8_t byte;
		for (int i = 0; i < getSize(); i++) {
			packet = getPacket(i);
			byte = packet->GetPayloadData()[0];
			if (i == 0) {
				if (byte == 0x00)
					startFound = true;
			}
			else if (i == getSize() - 1) {
				if (byte == 0xff)
					endFound = true;
			}
			else {
				if (byte != 0xff)
					midCorrect = false;
			}
		}

		return startFound && midCorrect && endFound;
	}

	return false;
}

void RTPFrame::sort() {
	std::sort($list.begin(), $list.end(), RTPCompare());
	$sorted = true;
}

bool RTPFrameComparer::operator()(RTPFrame* left, RTPFrame* right) {
	jrtplib::RTPPacket* leftHeader = left->getHeader();
	jrtplib::RTPPacket* rightHeader = right->getHeader();
	
	if (leftHeader == nullptr) {
		if (rightHeader == nullptr)
			return false;
		else {
			return true;
		}
	}
	if (rightHeader == nullptr) {
		return false;
	}

	return $compare(leftHeader, rightHeader);
}

uint16_t RTPFrame::getPacketNumber() {
	return $packetNumber;
}

uint32_t RTPFrame::getTimestamp() {
	return $timestamp;
}

void RTPFrame::print() {
	std::cout << "PN: " << getHeader()->GetSequenceNumber() << "\t TS: " << getHeader()->GetTimestamp() << "\t Type: " << getHeader()->GetPayloadType() << "\n";
	for (int i = 1; i < getSize(); i++) {
		jrtplib::RTPPacket* packet = getPacket(i);
		std::cout << "\tPN: " << packet->GetSequenceNumber() << "\t TS: " << packet->GetTimestamp() << "\t Type: " << packet->GetPayloadType() << "\n";
	}
}

void RTPFrame::clear() {
	$list.clear();
	$sorted = true;
}

uint8_t* RTPFrame::getRGB(int width, int height) {
    int lengthY = width * height;
    int lengthUV = lengthY / 4;
    int totalLength = lengthY + (lengthUV * 2);
    int bytesCollected = 0;
    int bytesToCollect = totalLength;
    jrtplib::RTPPacket* one = getPacket(0);
    jrtplib::RTPPacket* two = getPacket(1);
    jrtplib::RTPPacket* three = getPacket(2);
    jrtplib::RTPPacket* four = getPacket(3);
    int oneBytes = one->GetPayloadLength() - 9;
    int twoBytes = two->GetPayloadLength() - 1;
    int threeBytes = three->GetPayloadLength() - 1;
    int fourBytes = four->GetPacketLength() - 1;
    std::cout << "1: " << oneBytes << " 2: " << twoBytes << " 3: " << threeBytes << " 4: " << fourBytes << std::endl;

    uint8_t* buffer = new uint8_t[totalLength];

    memcpy(buffer, (one->GetPayloadData() + 9), oneBytes);
    bytesCollected = oneBytes;
    bytesToCollect -= oneBytes;

    memcpy((buffer + bytesCollected), (two->GetPayloadData() + 1), twoBytes);
    bytesToCollect -= twoBytes;
    bytesCollected += twoBytes;

    memcpy((buffer + bytesCollected), (three->GetPayloadData() + 1), threeBytes);
    bytesToCollect -= threeBytes;
    bytesCollected += threeBytes;

    if(bytesToCollect > 0) {
        memcpy(buffer + bytesCollected, four->GetPayloadData() + 1, min(fourBytes, bytesToCollect));
        bytesToCollect -= min(fourBytes, bytesToCollect);
        bytesCollected += min(fourBytes, bytesToCollect);
    }
    std::cout << "BytesToCollect: " << bytesToCollect;
    uint8_t* rgbBuffer = new uint8_t[lengthY * 4];
    convertYUVtoRGBA(buffer, width, height, rgbBuffer);
    delete[] buffer;
    return rgbBuffer;
}

void convertYUVtoRGBA(const unsigned char *pYUVFrame, int width, int height, unsigned char *pRGBA)
{
    int pixels = width*height;
    int pixels4 = pixels/4;
    int width2 = width/2;
    const unsigned char *pU = pYUVFrame + pixels;
    const unsigned char *pV = pU + pixels/4;

    int destPos = 0;

    for (int y = 0 ; y < height ; y++)
    {
        int yOffset = y * width;
        int y2 = y / 2;
        int y2Offset = y2 * width2;

        for (int x = 0 ; x < width ; x++)
        {
            int Y = (int)pYUVFrame[x+yOffset];
            int x2 = x/2;
            int pos2 = x2 + y2Offset;
            int U = (int)pU[pos2];
            int V = (int)pV[pos2];

            float Y16 = ((float)(Y) - 16.0f);
            float V128 = ((float)(V) - 128.0f);
            float U128 = ((float)(U) - 128.0f);

            float r = 1.164f*Y16 + 1.596f*V128;
            float g = 1.164f*Y16 - 0.813f*V128 - 0.391f*U128;
            float b = 1.164f*Y16 + 2.018f*U128;

            r = (r > 255.0)?255.0:r;
            g = (g > 255.0)?255.0:g;
            b = (b > 255.0)?255.0:b;
            r = (r < 0.0)?0.0:r;
            g = (g < 0.0)?0.0:g;
            b = (b < 0.0)?0.0:b;

            unsigned char R = (unsigned char)r;
            unsigned char G = (unsigned char)g;
            unsigned char B = (unsigned char)b;



            pRGBA[destPos++] = B;
            pRGBA[destPos++] = G;
            pRGBA[destPos++] = R;

            pRGBA[destPos++] = 0xff;
        }
    }
}

void RTPFrame::setPlayTime(qint64 time) {
    $playTime = time;
}

qint64 const RTPFrame::getPlayTime() {
    return $playTime;
}


bool RTPFramePlayTimeComparer::operator ()(RTPFrame* left, RTPFrame* right) {
    //std::cout << "Sort" << std::endl;
    qint64 time1 = left->getPlayTime();
    qint64 time2 = right->getPlayTime();
    return time1 > time2;
}

