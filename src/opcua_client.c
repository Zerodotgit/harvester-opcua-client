#include "opcua_client.h"
#include <open62541/client.h>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/plugin/log_stdout.h>

UA_Variant uaValue;
UA_StatusCode status;

//connect to OPCUA server
UA_Client* opcuaConnect(const char* serverUrl) {

    //create opcua client
    UA_Client * client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));

    //connect to opcua server
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Connecting to OPCUA server");
    status = UA_Client_connect(client, serverUrl);
    if (status != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Failed to connect to OPCUA server: %s", status);
        return NULL;
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Connected to OPCUA");

    return client;
}

//write value to OPCUA server
void opcuaWriteValue(UA_Client *client, UA_NodeId nodeId, double value) {

    UA_Variant_setScalar(&uaValue, &value, &UA_TYPES[UA_TYPES_DOUBLE]); //convert value to UA_Variant
    status = UA_Client_writeValueAttribute(client, nodeId, &uaValue);   //write value to OPCUA server
    if (status != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Failed to write value to OPCUA server: %s", status);
    }else {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_CLIENT, "Value written to OPCUA server");
    }

}

//disconnect OPCUA client
void disconnectOPCUAClient(UA_Client *client) {
    UA_Client_delete(client);
}