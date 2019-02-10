#include "myserver.h"

#include <signal.h>

UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

MyServer::MyServer()
{
}

bool MyServer::startServer()
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    // Create a server listening on port 4840
    UA_ServerConfig *config = UA_ServerConfig_new_default();
    UA_Server *server = UA_Server_new(config);

    manuallyDefineSystem(server);

    //Run the server loop
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);

    return (int)retval;
}

void MyServer::manuallyDefineSystem(UA_Server *server)
{
    // Add System object
    UA_NodeId systemId; // get the nodeid assigned by the server
    UA_ObjectAttributes osAttr = UA_ObjectAttributes_default;
    osAttr.displayName = UA_LOCALIZEDTEXT("en-US", "System");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "System"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            osAttr, NULL, &systemId);

    // Add Terminal object (under System object)
    UA_NodeId terminalId; // get the nodeid assigned by the server
    UA_ObjectAttributes otAttr = UA_ObjectAttributes_default;
    otAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Terminal");
    UA_Server_addObjectNode(server, UA_NODEID_NULL, systemId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "Terminal"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            otAttr, NULL, &terminalId);

    // Add Terminal object Open method
    UA_Argument openInputArgument;
    UA_Argument_init(&openInputArgument);
    // TODO:: add openInputArguments

    UA_Argument openOutputArgument;
    UA_Argument_init(&openOutputArgument);
    // TODO:: add openOutputArguments

    UA_MethodAttributes openAttr = UA_MethodAttributes_default;
    openAttr.displayName = UA_LOCALIZEDTEXT("en-US","Open");
    openAttr.executable = true;
    openAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NULL, terminalId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Open"),
                            openAttr, &openMethodCallback,
                            1, &openInputArgument, 1, &openOutputArgument, NULL, NULL);

    // Add Terminal object Run method
    UA_Argument runInputArgument;
    UA_Argument_init(&runInputArgument);
    // TODO:: add runInputArguments

    UA_Argument runOutputArgument;
    UA_Argument_init(&runOutputArgument);
    // TODO:: add runOutputArguments

    UA_MethodAttributes runAttr = UA_MethodAttributes_default;
    runAttr.displayName = UA_LOCALIZEDTEXT("en-US","Run");
    runAttr.executable = true;
    runAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NULL, terminalId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Run"),
                            runAttr, &runMethodCallback,
                            1, &runInputArgument, 1, &runOutputArgument, NULL, NULL);

    // Add Terminal object Close method
    UA_Argument closeInputArgument;
    UA_Argument_init(&closeInputArgument);
    // TODO:: add closeInputArguments

    UA_Argument closeOutputArgument;
    UA_Argument_init(&closeOutputArgument);
    // TODO:: add closeOutputArguments

    UA_MethodAttributes closeAttr = UA_MethodAttributes_default;
    closeAttr.displayName = UA_LOCALIZEDTEXT("en-US","Close");
    closeAttr.executable = true;
    closeAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_NULL, terminalId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Close"),
                            closeAttr, &closeMethodCallback,
                            1, &closeInputArgument, 1, &closeOutputArgument, NULL, NULL);

}


UA_StatusCode MyServer::openMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Method is not implemented yet!");
    return UA_STATUSCODE_BADNOTIMPLEMENTED;
}

UA_StatusCode MyServer::runMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Method is not implemented yet!");
    return UA_STATUSCODE_BADNOTIMPLEMENTED;
}

UA_StatusCode MyServer::closeMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Method is not implemented yet!");
    return UA_STATUSCODE_BADNOTIMPLEMENTED;
}
