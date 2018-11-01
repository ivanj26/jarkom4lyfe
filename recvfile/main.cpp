#include <stdlib.h>
#include <sstream>
#include "utility.h"
#include "receiver.h"

int main(int argc, char *argv[]) {
	stringstream portStr;
	stringstream windowSizeStr;
	stringstream bufferSizeStr;

	portStr << argv[4];
	windowSizeStr << argv[2];
	bufferSizeStr << argv[3];

	unsigned int port;
	unsigned int windowSize;
	unsigned int bufferSize;

	bufferSizeStr >> bufferSize;
	windowSizeStr >> windowSize;
	portStr >> port;

	Receiver r(port, windowSize, bufferSize);
	r.listen();

	char *p = argv[1];
	r.saveToFile(p);
	return 0;
}
