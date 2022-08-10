#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "SocketServer.h"

int main()
{
    SocketServer server;
    server.startServer();
    return 0;
};