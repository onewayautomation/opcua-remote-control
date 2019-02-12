#include "myserver.h"

#include <signal.h>
#include <windows.h>

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

    // Add object
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "SystemObj");
    UA_Server_addObjectNode(m_server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "SystemObj"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &m_systemObjId);

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


UA_StatusCode MyServer::openMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    // Open cmd window
    STARTUPINFOA si;
    ZeroMemory(&si,sizeof(STARTUPINFO));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    char cmd_exe[32767];
    GetEnvironmentVariableA("COMSPEC", cmd_exe, 32767);
    if (CreateProcessA(cmd_exe, "/k", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "dwProcessId =" + pi.dwProcessId);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
    else
    {
        DWORD dwErrorCode = GetLastError();
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "cmd process not started, error =" + dwErrorCode);
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Open was called");
    return UA_STATUSCODE_GOOD;
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

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Method is not implemented yet!");
    return UA_STATUSCODE_BADNOTIMPLEMENTED;
}

UA_StatusCode MyServer::closeMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

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
