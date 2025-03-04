#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "opcua_client.h"
#include "socket_server.h"

#define OPCUA_SERVER_URL "opc.tcp://192.168.31.144:4840"
#define SOCKET_PORT 8000
#define BUFFER_SIZE 1024

int keepRunning = 1;

void handleSignal(int sig) {
    keepRunning = 0;
}

int main() {

    //connect to OPCUA server
    UA_Client *client = opcuaConnect(OPCUA_SERVER_URL);
    if (!client) {
        perror("Failed to connect to UA_Server");
        return EXIT_FAILURE;
    }

    //node ids
    UA_NodeId leftWheel = UA_NODEID_STRING(1, "Left Wheel");
    UA_NodeId rightWheel = UA_NODEID_STRING(1, "Right Wheel");
    UA_NodeId harvest = UA_NODEID_STRING(1, "Harvest");
    UA_NodeId push = UA_NODEID_STRING(1, "Push");

    int serverFd = createSocket(SOCKET_PORT);   //create socket server
    int newSocket = acceptConnection(serverFd); //accept connection from client

    char buffer[BUFFER_SIZE] = {0};

    signal(SIGUSR1, handleSignal);

    double value = 0;
    double value1 = 0;
    double value2 = 0;

    //read message from client and write to OPCUA server
    while (keepRunning) {
        const char *response = "Received";

        //read message from client
        read(newSocket, buffer, BUFFER_SIZE);
        printf("Client: %s\n", buffer);

        value = strtod(buffer, NULL);
        value1 = 1 / 3.3 * value;

        if (value == 0)
            value2 = 0;
        else
            value2 = 300;

        opcuaWriteValue(client, leftWheel, value);
        opcuaWriteValue(client, rightWheel, value);
        opcuaWriteValue(client, harvest, value1);
        opcuaWriteValue(client, push, value2);

        if (send(newSocket, response, strlen(response), 0) < 0) {
            perror("Failed to respond to client:");
            break;
        }
    }

    closeSocket(newSocket);
    closeSocket(serverFd);
    disconnectOPCUAClient(client);

    return 0;
}