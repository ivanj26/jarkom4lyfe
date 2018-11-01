#ifndef SENDER_H
#define SENDER_H

#define TIMEOUT 5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include "utility.h"
#include "UdpClient.h"
#include "packet.h"

class Sender {
	public:
	  Sender(int, int, char*);
	  ~Sender();

	  void readFile(char *);

	  void slider();

	  static void *listener(void *);
		static int buffersize;

	private:
		int len;
		int lws;
		int windowsize;
		bool status;
		UdpClient rclient;
		std::vector<Packet> datastorage;
		std::vector<int> acks;
};

#endif
