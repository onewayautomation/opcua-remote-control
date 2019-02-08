#ifndef MYSERVER_H
#define MYSERVER_H

#include "open62541.h"

class MyServer
{
public:
    MyServer();
    ~MyServer();

    bool startServer();

    static UA_StatusCode openTerminalMethodCallback(UA_Server *server,
                             const UA_NodeId *sessionId, void *sessionHandle,
                             const UA_NodeId *methodId, void *methodContext,
                             const UA_NodeId *objectId, void *objectContext,
                             size_t inputSize, const UA_Variant *input,
                             size_t outputSize, UA_Variant *output);
    void addOpenTerminalMethod(UA_Server *server);

    static UA_StatusCode runTerminalCmdMethodCallback(UA_Server *server,
                             const UA_NodeId *sessionId, void *sessionHandle,
                             const UA_NodeId *methodId, void *methodContext,
                             const UA_NodeId *objectId, void *objectContext,
                             size_t inputSize, const UA_Variant *input,
                             size_t outputSize, UA_Variant *output);
    void addRunTerminalCmdMethod(UA_Server *server);

    static UA_StatusCode closeTerminalMethodCallback(UA_Server *server,
                             const UA_NodeId *sessionId, void *sessionHandle,
                             const UA_NodeId *methodId, void *methodContext,
                             const UA_NodeId *objectId, void *objectContext,
                             size_t inputSize, const UA_Variant *input,
                             size_t outputSize, UA_Variant *output);
    void addCloseTerminalMethod(UA_Server *server);

private:
    UA_NodeId m_systemObjId; // Get the nodeid assigned by the server
    UA_Server *m_server;
};

#endif // MYSERVER_H
