#include "AudioCD.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	AudioCD cd1;
	cd1.PrintCD();
	cd1.SetArtist("Brent");
	cd1.SetTracks(1);
	cd1.SetTitle("Brent en de 7 negers");
	cd1.SetPrice(15);
	cd1.PrintCD();

	AudioCD cd2("Brent en de 8 negers", 14, "Brent", 1);
	cd2.PrintCD();
	return 0;
}

AudioCD::AudioCD(): Artikel(), artist(""), tracks(0) {
}

AudioCD::AudioCD(AudioCD &audioCd): Artikel(audioCd.GetTitle(), audioCd.GetPrice()), artist(artist), tracks(tracks) {
}

void AudioCD::PrintCD() {
	PrintArtikel();
	cout << "Artiest:" << artist << "\n";
	cout << "Tracks:\t" << tracks << "\n";
}


AudioCD::AudioCD(string title, int price, string artist, int tracks): Artikel(title, price), artist(artist), tracks(tracks) {
}