#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "127.0.0.1" 
#define BUFLEN 1024        
#define PORT 8080        

class UDPSocket {
protected:
    int s; 

public:
    UDPSocket();
    virtual ~UDPSocket();

    int SendDatagram(char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen);
    int RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen);
};