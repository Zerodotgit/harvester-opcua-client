#ifndef OPCUA_CLIENT_H
#define OPCUA_CLIENT_H

#include <open62541/client.h>

UA_Client* opcuaConnect(const char* serverUrl);
void opcuaWriteValue(UA_Client *client, UA_NodeId nodeId, double value);
void disconnectOPCUAClient(UA_Client *client);

#endif //OPCUA_CLIENT_H
