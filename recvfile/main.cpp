#include <stdlib.h>
#include "utility.h"
#include "receiver.h"

#define PORT 50000
#define WINDOWSIZE 4

int main(int argc, char const *argv[]) {
	Receiver r(PORT, WINDOWSIZE);
	r.listen();
	char *p = (char*) "received";
	r.saveToFile(p);
	return 0;
}