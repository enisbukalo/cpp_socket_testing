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

class SocketServer
{
    private:
        int createSocket();
        int bindSocket();
        int markListening();
        int waitConnection();
        void closeListening();
        void closeSocket();

        int listeningSocket;
        std::string socketNumber;
        sockaddr_in hint;
        sockaddr_in clientIn;
        static constexpr socklen_t clientSize = sizeof(clientIn);
        char host[NI_MAXHOST];
        char host[NI_MAXSERV];
        int clientSocket;
        char messageBuffer[4096];
        std::string messageIn;
    public:
        void startServer();
        int serverLoop();
        void stopServer();
        SocketServer();
        ~SocketServer();
};

#endif