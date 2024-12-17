#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UDPServer.h"

#define BUFLEN 1024 
#define PORT 8888  

int main(int argc, char* argv[]) {
    struct sockaddr_in si_other;
    unsigned short srvport;
    int slen;
    char buf[BUFLEN];
    char msg[BUFLEN];

    srvport = (1 == argc) ? PORT : atoi(argv[1]);
    UDPServer server(srvport);

    slen = sizeof(si_other);

    while (1) {
        printf("Waiting for data... ");
        fflush(stdout);

        memset(buf, '\0', BUFLEN);

        server.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);

        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n", buf);

        printf("\nAnswer: ");
        fgets(msg, BUFLEN, stdin);
        msg[strcspn(msg, "\n")] = '\0';

        server.SendDatagram(msg, (int)strlen(msg), (struct sockaddr*)&si_other, slen);
    }

    return 0;
}