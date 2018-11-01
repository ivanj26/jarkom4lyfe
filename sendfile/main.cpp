#include "utility.h"
#include "sender.h"
#include <sstream>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	stringstream portStr;
	stringstream windowSizeStr;
	stringstream bufferSizeStr;

	portStr << argv[5];
	windowSizeStr << argv[2];
	bufferSizeStr << argv[3];

	unsigned int port;
	unsigned int windowSize;
	unsigned int bufferSize;

	bufferSizeStr >> bufferSize;
	windowSizeStr >> windowSize;
	portStr >> port;

	Sender::buffersize = bufferSize;

	Sender s(port, windowSize, argv[4]);

	char *p = argv[1];

	s.readFile(p);
	pthread_t th;
	pthread_create(&th, NULL, s.listener, &s);
	s.slider();
	return 0;
}
