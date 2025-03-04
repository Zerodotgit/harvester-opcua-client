#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

int createSocket(int port);
int acceptConnection(int serverFd);
void closeSocket(int serverFd);

#endif //SOCKET_CLIENT_H
