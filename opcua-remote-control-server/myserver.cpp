#include "myserver.h"
#include "open62541.h"
#include <signal.h>

UA_Boolean running = true;
static void stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
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

    //Run the server loop
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);

    return (int)retval;
}
