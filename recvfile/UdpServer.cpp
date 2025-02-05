#include "UdpServer.h"
#include <unistd.h>
#include <string.h>
#include <cstdio>

UdpServer::UdpServer(const std::string& addr, int port) : f_port(port), f_addr(addr) {
  char decimal_port[16];
  snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);
  decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = IPPROTO_UDP;
  int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo));
  if(r != 0 || f_addrinfo == NULL) {
      // throw udp_client_  server_runtime_error(("invalid address or port for UDP socket: \"" + addr + ":" + decimal_port + "\"").c_str());
  }
  f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
  if(f_socket == -1) {
    freeaddrinfo(f_addrinfo);
    // throw udp_client_server_runtime_error(("could not create UDP socket for: \"" + addr + ":" + decimal_port + "\"").c_str());
  }
  r = bind(f_socket, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
  if(r != 0) {
    freeaddrinfo(f_addrinfo);
    close(f_socket);
    // throw udp_client_server_runtime_error(("could not bind UDP socket with: \"" + addr + ":" + decimal_port + "\"").c_str());
  }
}

UdpServer::~UdpServer() {
  freeaddrinfo(f_addrinfo);
  close(f_socket);
}

int UdpServer::getSocket() const {
  return f_socket;
}

int UdpServer::getPort() const {
  return f_port;
}

string UdpServer::getAddr() const {
  return f_addr;
}

int UdpServer::recv(char *msg, size_t max_size) {
  return ::recv(f_socket, msg, max_size, 0);
}

int UdpServer::recvfrom(char *msg, size_t max_size, sockaddr_in& sender, uint& senderaddrsize) {
  return ::recvfrom(f_socket, msg, max_size, 0, (sockaddr*) &sender, &senderaddrsize);
}

int UdpServer::send(const char *msg, size_t size, sockaddr_in dest) {
  return sendto(f_socket, msg, size, 0, (sockaddr*) &dest, sizeof(dest));
}
