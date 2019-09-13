#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct album {
	char artist[50];
	char title[50];
	int year;
	int songAmount;
	char songs[30][50];
	struct album* next;
	struct album* prev;
} album;

void readNewAlbum(album**);
void addAlbum(album**, char const*, char const*, int const);
void printList(album*);
void testAdd(album**);
void addSongs(album* album);
void addSongsToAlbum(album* head);
void freeEverything(album**);
void genIndex(album*, int[]);
void printIndex(int[]);
void writeToFile(album*, int[], char*);
void readFromFile(char*, char*);


int main(int argc, char const *argv[])
{
	int index[26];
	album* list = NULL;
	testAdd(&list);
	printList(list);
	addSongsToAlbum(list);
	printList(list);
	genIndex(list, index);
	printIndex(index);
	writeToFile(list, index, "IndexList.txt");
	readFromFile("Zwagger", "IndexList.txt");
	freeEverything(&list);

	return 0;
}

void readNewAlbum(album** head) {
	char* title;
	char* artist;
	int year;
	int letters;

	printf("Give the album title: ");
	letters = scanf("%s", title);
	printf("Give the album artist: ");
	letters = scanf("%s", artist);
	printf("Give the album year: ");
	letters = scanf("%d", &year);

	addAlbum(head, artist, title, year);
}

void addSongsToAlbum(album* head) {
	album* pointer = head;
	char tempArtist[50];
	char tempTitle[50];
	int letters;
	printf("Give the artist who made the album: ");
	letters = scanf("%s", tempArtist);
	printf("Give the name of the album: ");
	letters = scanf("%s", tempTitle);

	while(pointer != NULL && !(strcmp(tempArtist, pointer->artist) == 0 && strcmp(tempTitle, pointer->title) == 0))
		pointer = pointer->next;

	if(pointer == NULL) 
		printf("ERROR: Function \"addSongsToAlbum\": Album(%s) of artist(%s) not found.\n", tempTitle, tempArtist);
	else {
		addSongs(pointer);
	}

}

void addSongs(album* album) {
	char tempSong[50];
	int i;
	int* letters;

	printf("Enter the name of the song or type Stop to stop.\n");
	letters = (int*) fgets(tempSong, 49, stdin);

	if(tempSong[strlen(tempSong) - 1] == '\n')
		tempSong[strlen(tempSong) - 1] = '\0';
	if(tempSong[0] >= 'a' && tempSong[0] <= 'z')
		tempSong[0] = (tempSong[0] - 'a') + 'A';

	for(i = 0; strcmp(tempSong, "Stop") != 0 && i < 30; i++) {
		strcpy(album->songs[i], tempSong);
		(album->songAmount)++;
		letters = (int*) fgets(tempSong, 49, stdin);
		if(tempSong[strlen(tempSong) - 1] == '\n')
			tempSong[strlen(tempSong) - 1] = '\0';
		if(tempSong[0] >= 'a' && tempSong[0] <= 'z')
			tempSong[0] = (tempSong[0] - 'a') + 'A';
	}
}

void addAlbum(album** head, char const* artist, char const* title, int const year) {
	album* pointer = *head;
	album* newAlbum = (album*) malloc(sizeof(album));
	if(newAlbum == NULL) {
		printf("ERROR: Function \"addAlbum\": Couldn't reserve memory for new album.\n");
		return;
	}


	strcpy(newAlbum->artist, artist);
	strcpy(newAlbum->title, title);
	newAlbum->year = year;
	newAlbum->prev = NULL;
	newAlbum->next = NULL;
	newAlbum->songAmount = 0;

	if(pointer == NULL) {
		*head = newAlbum;
		return;
	}


	while(pointer->next != NULL && strcmp(pointer->artist, newAlbum->artist) < 0) {
		pointer = pointer->next;
	}

	if(strcmp(pointer->artist, newAlbum->artist) > 0) {
		newAlbum->next = pointer;
		if(pointer->prev == NULL) {
			*head = newAlbum;
		}
		else {
			pointer->prev->next = newAlbum;
			pointer->prev = newAlbum;
		}
	}
	else if(strcmp(pointer->artist, newAlbum->artist) < 0){
		pointer->next = newAlbum;
		newAlbum->prev = pointer;
	}
	else {
		if(strcmp(pointer->title, newAlbum->title) == 0) {
			printf("WARNING: Function \"addAlbum\": Duplicate album, new Album ignored\n");
			free(newAlbum);
		}
		else {
			newAlbum->next = pointer;
			if(pointer->prev == NULL) {
				*head = newAlbum;
			}
			else {
				pointer->prev->next = newAlbum;
				pointer->prev = newAlbum;
			}
		}
	}


}

void genIndex(album* start, int index[26]) {
	album* pointer = start;
	int i;
	for(i = 0; i < 26; i++) {
		index[i] = -1;
	}

	i = 0;
	char prevChar;
	while(pointer != NULL) {
		prevChar = pointer->artist[0];
		if(prevChar >= 'A' && prevChar <= 'Z' && index[prevChar - 'A'] == -1)
			index[prevChar - 'A'] = i;
		i++;
		pointer = pointer->next;

	}
}

void printIndex(int index[26]) {
	int i;

	for(i = 0; i < 26; i++) {
		printf("%c begint op: %d\n", i + 'A', index[i]);
	}
}

void printList(album* start) {
	int i;
	while(start != NULL) {
		printf("Artist: %s, Title: %s, Year: %d.\n", start->artist, start->title, start->year);
		if(start->songAmount != 0)
			printf("Songs:");
		for(i = 0; i < start->songAmount; i++) {
			printf("\t%s\n", start->songs[i]);
		}
		start = start->next;
	}
}

void testAdd(album** head) {
	int i;
	char artist[8] = "Swagger";
	char album[5] = "Yolo";
	int year = 1996;

	for(i = 0; i < 20; i++) {
		if(i % 2)
			artist[0] = 'A' + i;
		else
			artist[0] = 'Z' - i;
		addAlbum(head, artist, album, year + i);
	}
}

void freeEverything(album** head) {
	album* pointer = *head;
	*head == NULL;
	if(pointer == NULL) {
		printf("WARNING: Function\"freeEverything\": Empty List.\n");
	}
	if(pointer->next == NULL)
		free(pointer);
	else {
		pointer = pointer->next;
		while(pointer->next != NULL) {
			free(pointer->prev);
			pointer = pointer->next;
		}
	}

	free(pointer->prev);
	free(pointer);
	printf("Everything is free!\n");
}

void writeToFile(album* start, int index[26], char* fileName) {
	FILE* file = fopen(fileName, "w");
	int i;
	if(file == NULL) {
		printf("ERROR: Function \"writeToFile\": Cannot open file.\n");
		return;
	}

	fprintf(file,"Index:\n");
	for(i = 0; i < 26; i++) {
		if(index[i] == -1)
			fprintf(file, "\tLetter '%c' is not in the list.\n", 'A' + i);
		else
			fprintf(file, "\tLetter '%c' is in the list at position: %d\n", 'A' + i, index[i]);
	}

	fprintf(file, "\nList:\n");
	while(start != NULL) {
		fprintf(file, "\tAlbum \"%s\" of artist \"%s\" made in year %d contains the following songs:", start->title, start->artist, start->year);
		if(start->songAmount == 0)
			fprintf(file, "\n\t\tNone\n");
		else {
			for(i = 0; i < start->songAmount; i++) {
				fprintf(file, "\t\t%s\n", start->songs[i]);
			}
		}
		start = start->next;
	}

	fclose(file);


}

void readFromFile(char* artist, char* fileName) {
	FILE* file = fopen(fileName, "r");
	char buffer[255];
	char number[10];
	int i;
	int j;
	int numbar;
	char ch = artist[0];
	int* derp;

	while(!feof(file)) {
		derp = (int*) fgets(buffer, 254, file);
		for(i = 0; i < strlen(buffer) && buffer[i] != '\''; i++) {
		}
		if(buffer[i + 1] == ch) {
			while(i < strlen(buffer) && buffer[i] < '0' && buffer[i] > '9') {
				i++;
			}

			if(buffer[i] >= '0' && buffer[i] <= '9') {
				number[0] = '\0';
				for(j = 0;i < strlen(buffer); i++, j++) {
					number[j] = buffer[i];
				}
				number[j] = '\0';
			}

		}
		printf("Array: %s", number);
		numbar = atoi(number);

		printf("Number: %d\n", numbar);
	}
}