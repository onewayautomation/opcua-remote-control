#include "myserver.h"

#ifdef WIN32
#pragma comment (lib, "Ws2_32.lib")
#endif

int main(int argc, char *argv[])
{
    MyServer myserver;
    myserver.startServer();

		return 0;
}
