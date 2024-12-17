#include "UDPSocket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UDPSocket::UDPSocket() {
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
}

UDPSocket::~UDPSocket() {
    close(s);
}

int UDPSocket::SendDatagram(char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen) {
    if (sendto(s, msg, msglen, 0, si_dest, slen) < 0) {
        perror("sendto() failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int UDPSocket::RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen) {
    if (recvfrom(s, buf, buflen, 0, si_dest, (socklen_t*)slen) < 0) {
        perror("recvfrom() failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}