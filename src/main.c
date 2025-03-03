#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <open62541/client.h>
#include <open62541/client_config_default.h>

#define PORT 8000

#define OPCUA_SERVER_SERVER_URL "opc.tcp://localhost:4840"

int keepRunning = 1;

// signal handler
void handleSignal(int sig)
{
    keepRunning = 0;
}

int main()
{
    //=============opcua client================

    //create opcua client
    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));

    //connect to opcua server
    printf("Connecting to OPCUA server\n");
    UA_StatusCode status = UA_Client_connect(client, OPCUA_SERVER_SERVER_URL);
    if (status != UA_STATUSCODE_GOOD)
    {
        UA_Client_delete(client);
        return status;
    }


    //=============socket server================
    double value = 0;
    double value1 = 0;

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrLen = sizeof(address);
    char buffer[1024] = {0};    //get message
    const char *response = "1";  //answer message

    //create socket
    printf("Creating socket...\n");
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("create socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    printf("Done\n");

    //bind socket
    printf("Binding socket...\n");
    if (bind(server_fd, (struct sockaddr *)&address, addrLen) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Done\n");

    //listen connection
    printf("Listening...\n");
    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Done\n");

    //accept connection
    printf("Waiting for connection...\n");
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrLen)) < 0)
    {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected\n");

    while (true)
    {
        //read message
        read(new_socket, buffer, 1024);
        printf("Client:%s\n", buffer);

        //the value that will be sent to the OPCUA server
        value = strtod(buffer, NULL);
        value1 = 1/3.3 * value;



        //respond message
        if (send(new_socket, response, strlen(response), 0) < 0)
        {
            perror("respond failed");
            close(new_socket);
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        //ctrl + c signal handler
        signal(SIGINT, handleSignal);

        if (keepRunning == 0)
            break;
    }
    close(new_socket);
    close(server_fd);
    printf("exited\n");

    return 0;

}