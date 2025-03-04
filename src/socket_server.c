#include "socket_server.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int createSocket(int port) {
    int serverFd;
    struct sockaddr_in address;

    //create socket
    printf("Creating socket...\n");
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create socket:");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    //bind socket
    printf("binding socket...\n");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Failed to bind socket:");
        exit(EXIT_FAILURE);
    }
    printf("Socket binded successfully.\n");

    //listen connection
    printf("Waiting for connection...\n");
    if (listen(serverFd, 5) < 0) {
        perror("Failed to listen on socket:");
        exit(EXIT_FAILURE);
    }

    return serverFd;
}

int acceptConnection(int serverFd) {
    int newSocket;
    struct sockaddr_in address;

    socklen_t addrLen = sizeof(address);

    //accept connection
    if ((newSocket = accept(serverFd, (struct sockaddr*)&address, &addrLen)) < 0) {
        perror("Failed to accept connection:");
        close(serverFd);
        exit(EXIT_FAILURE);
    }
    // printf("Connected\n");

    return newSocket;

}

void closeSocket(int serverFd) {
    close(serverFd);
}