#include "utility.h"
#include "sender.h"
#include <stdlib.h>

#define PORT 50000
#define WINDOWSIZE 4

int main(int argc, char const *argv[]) {
	Sender s(PORT, WINDOWSIZE);
	char *p = (char*) "sender.h";
	s.readFile(p);
	pthread_t th;
	pthread_create(&th, NULL, s.listener, &s);
	s.slider();
	return 0;
}