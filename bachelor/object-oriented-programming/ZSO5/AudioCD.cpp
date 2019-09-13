#include "AudioCD.h"
#include <iostream>

/*int main(int argc, char const *argv[])
{
	Artikel* ptr;
	AudioCD cd2("Brent en de 8 negers", 14, "Brent", 1);
	cd2.Toon();

	ptr = &cd2;
	ptr->Toon();
	return 0;
}*/

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

void AudioCD::Toon() {
	cout << "AudioCD:\n\tNaam:\t" << this->title << "\n\tPrijs:\t" << this->price << "\n\tArtiest:" << artist << "\n\tTracks:\t" << tracks << "\n";
}