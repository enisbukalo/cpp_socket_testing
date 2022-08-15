#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "MessageQueue.h"

class SocketServer
{
    private:
        int createSocket();
        int bindSocket();
        int markListening();
        int waitConnection();
        void parseIncoming();
        void closeSocket(int);

        int listeningSocket;
        std::string socketNumber;
        sockaddr_in hint;
        sockaddr_in clientIn;
        socklen_t clientSize = sizeof(clientIn);
        char host[NI_MAXHOST];
        char service[NI_MAXSERV];
        int clientSocket;
        char messageBuffer[4096];
        std::string messageIn;
        MessageQueue messageQueue;
    public:
        void startServer();
        int serverLoop();
        void stopServer();
        SocketServer();
        ~SocketServer();
};

#endif