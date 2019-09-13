#ifndef AUDIOCD_H
#define AUDIOCD_H
#include <string>
#include "Artikel.h"
using namespace std;

class AudioCD: public Artikel {
public:
	AudioCD();
	AudioCD(string title, int price, string artist, int tracks);
	AudioCD(AudioCD &audioCd);
	int GetTracks() {return this->tracks;}
	string GetArtist() {return this->artist;}
	void SetTracks(int tracks) {this->tracks = tracks;}
	void SetArtist(string artist) {this->artist = artist;}
	void PrintCD();
private:
	string artist;
	int tracks;
};


#endif