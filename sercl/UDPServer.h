#pragma once
#include "UDPSocket.h"

class UDPServer : public UDPSocket {
private:
    unsigned short mServerPort;
    struct sockaddr_in mServer;
    UDPServer();

public:
    UDPServer(unsigned short serverport);
    virtual ~UDPServer();
};