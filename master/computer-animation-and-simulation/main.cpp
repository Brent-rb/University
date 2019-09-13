#define GLEW_STATIC
#include "SWindow.h"

int main(int argc, const char* argv[]) {
	const char* inFile = nullptr,*outFile = nullptr;
	if(argc >= 2) {
		inFile = argv[1];
	}
	if(argc >= 3) {
		outFile = argv[2];
	}

	SWindow* window;
	window = new SWindow(1600, 900, false, "Project CAS", inFile, outFile);
	window->run();
	return 0;
}