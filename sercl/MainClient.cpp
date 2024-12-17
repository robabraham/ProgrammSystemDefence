#include "UDPSocket.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);

    char buf[BUFLEN];
    char message[BUFLEN];

    unsigned short srv_port = 0;
    char srv_ip_addr[40];
    memset(srv_ip_addr, 0, 40);

    // Create socket
    UDPSocket client_sock;

    // Setup address structure
    memset((char*)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;

    if (1 == argc) {
        si_other.sin_port = htons(PORT);
        inet_pton(AF_INET, SERVER, &si_other.sin_addr);
        printf("1: Server - addr=%s , port=%d\n", SERVER, PORT);
    } else if (2 == argc) {
        si_other.sin_port = htons(atoi(argv[1]));
        inet_pton(AF_INET, SERVER, &si_other.sin_addr);
        printf("2: Server - addr=%s , port=%d\n", SERVER, atoi(argv[1]));
    } else {
        si_other.sin_port = htons(atoi(argv[2]));
        inet_pton(AF_INET, argv[1], &si_other.sin_addr);
        printf("3: Server - addr=%s , port=%d\n", argv[1], atoi(argv[2]));
    }

    // Start communication loop
    while (1) {
        printf("\nEnter message: ");
        fgets(message, BUFLEN, stdin);

        // Remove newline character from input
        message[strcspn(message, "\n")] = '\0';

        // Send the message
        client_sock.SendDatagram(message, (int)strlen(message), (struct sockaddr*)&si_other, slen);

        // Receive a reply and print it
        memset(buf, '\0', BUFLEN); // Clear the buffer
        client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);
        puts(buf);
    }

    return 0;
}