#include "myserver.h"

#include <signal.h>

UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

MyServer::MyServer()
{
}

MyServer::~MyServer()
{
    UA_Server_delete(m_server);
}

bool MyServer::startServer()
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    // Create a server listening on port 4840
    UA_ServerConfig *config = UA_ServerConfig_new_default();
    m_server = UA_Server_new(config);

    // Add object
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "SystemObj");
    UA_Server_addObjectNode(m_server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "SystemObj"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &m_systemObjId);

    // Add methods
    addOpenTerminalMethod(m_server);
    addRunTerminalCmdMethod(m_server);
    addCloseTerminalMethod(m_server);

    //Run the server loop
    UA_StatusCode retval = UA_Server_run(m_server, &running);
    UA_ServerConfig_delete(config);

    return (int)retval;
}

UA_StatusCode MyServer::openTerminalMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Method is not implemented yet!");
    return UA_STATUSCODE_BADNOTIMPLEMENTED;
}

void MyServer::addOpenTerminalMethod(UA_Server *server) {

    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);

    UA_MethodAttributes openTerminalAttr = UA_MethodAttributes_default;
    openTerminalAttr.description = UA_LOCALIZEDTEXT("en-US","Method to open terminal");
    openTerminalAttr.displayName = UA_LOCALIZEDTEXT("en-US","Open Terminal");
    openTerminalAttr.executable = true;
    openTerminalAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NULL, m_systemObjId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "openTerminal"),
                            openTerminalAttr, &openTerminalMethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
}

UA_StatusCode MyServer::runTerminalCmdMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Method is not implemented yet!");
    return UA_STATUSCODE_BADNOTIMPLEMENTED;
}

void MyServer::addRunTerminalCmdMethod(UA_Server *server) {

    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);

    UA_MethodAttributes runTerminalCmdAttr = UA_MethodAttributes_default;
    runTerminalCmdAttr.description = UA_LOCALIZEDTEXT("en-US","Method to run terminal cmd");
    runTerminalCmdAttr.displayName = UA_LOCALIZEDTEXT("en-US","Run Terminal Cmd");
    runTerminalCmdAttr.executable = true;
    runTerminalCmdAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NULL, m_systemObjId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "runTerminalCmd"),
                            runTerminalCmdAttr, &runTerminalCmdMethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
}

UA_StatusCode MyServer::closeTerminalMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Method is not implemented yet!");
    return UA_STATUSCODE_BADNOTIMPLEMENTED;
}

void MyServer::addCloseTerminalMethod(UA_Server *server) {

    UA_Argument inputArgument;
    UA_Argument_init(&inputArgument);

    UA_Argument outputArgument;
    UA_Argument_init(&outputArgument);

    UA_MethodAttributes closeTerminalAttr = UA_MethodAttributes_default;
    closeTerminalAttr.description = UA_LOCALIZEDTEXT("en-US","Method to close terminal");
    closeTerminalAttr.displayName = UA_LOCALIZEDTEXT("en-US","Close Terminal");
    closeTerminalAttr.executable = true;
    closeTerminalAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NULL, m_systemObjId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "closeTerminal"),
                            closeTerminalAttr, &closeTerminalMethodCallback,
                            1, &inputArgument, 1, &outputArgument, NULL, NULL);
}

