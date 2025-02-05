#include "sender.h"

Sender::Sender(int port, int windowsize) : rclient("127.0.0.1", port) {
	this->windowsize = windowsize;
	lws = 0;
	status = true;
	buffersize = BUFFER_SIZE;
}

Sender::~Sender() {

}

void Sender::readFile(char * filename) {
	int i;
	FILE * fin = fopen(filename, "rb");

	fseek(fin, 0, SEEK_END);
	unsigned long int size = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	len = (size / buffersize) + 1;

	for (i = 0; i<len; i++) {
		int nread;
		Packet p;
		char data[buffersize];

		nread = fread(data, sizeof(char), buffersize, fin);
		p.setHeader(0x01);
		p.setSeqNum(i+1);
		p.setData(data, nread);

		p.createBuffer();

		datastorage.push_back(p);
		acks.push_back(0);
	}

	fclose(fin);
	char temp[1];
	Packet p1;
	p1.setHeader(0x01);
	p1.setSeqNum(i);
	p1.setData(temp, 0);
	p1.createBuffer();
	datastorage.push_back(p1);
	acks.push_back(0);
	printf("%d\n", len);
}

void Sender::slider() {
	int i;

	while (true) {
		for (i=0; i<windowsize; i++) {
			if (lws+i >= len) {
				continue;
			} else {
				if (acks[lws+i] == 0) {
					printf("[+] Send Packet No. %d\n", lws+i+1);
					rclient.send(datastorage[lws+i].getBuffer(), datastorage[lws+i].getLen()+10);
					acks[lws+i] = TIMEOUT;
				} else {
					acks[lws+i]--;
				}
			}
		}

		if (lws >= len)
			break;
		sleep(1);
	}

	while (true) {
		if (acks[lws] == 0) {
			rclient.send(datastorage[lws].getBuffer(), datastorage[lws].getLen()+10);
			acks[lws] = TIMEOUT;
		} else {
			acks[lws]--;
		}

		if (!status)
			break;
		sleep(1);
	}
}

void* Sender::listener(void * tSender) {
	char msgrecv[BUFFER_SIZE+10];
	Sender* gSender = (Sender *) tSender;

	while (true) {
		if (gSender->rclient.recv(msgrecv, BUFFER_SIZE+10)) {
			Packet precv(msgrecv);

			printf("[+] Received new packet\n");

			if (precv.isValid()) {

				printf("[+] Get ACK %d\n", precv.getSeqNum());

				if (precv.getSeqNum() == 0) {
					gSender->status = false;
					break;
				}
				
				gSender->acks[precv.getSeqNum()-1] = -1;

			} else {
				printf("[-] Bad Packet Received\n");
			}

			while (gSender->acks[gSender->lws] == -1) {
				gSender->lws++;
			}

		}
	}
}