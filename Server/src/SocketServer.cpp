#include "SocketServer.h"

SocketServer::SocketServer()
{
    socketNumber = std::getenv("server_socket");
    if (!socketNumber.empty()){
        std::cout << "Socket Number: " << socketNumber << std::endl;
    }
    else{
        std::cerr << "Env variable 'SOCKET_SERVER' doesn't exist. Make sure it is set." << std::endl; 
        exit(0);
    }
}

void SocketServer::startServer()
{
    listeningSocket = createSocket();
}

int SocketServer::serverLoop()
{
    return 0;
}

int SocketServer::createSocket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int SocketServer::bindSocket()
{
    hint.sin_family = AF_INET;
    hint.sin_port = htons(std::stoi(socketNumber));
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    return bind(listeningSocket, (sockaddr *)&hint, sizeof(hint));
}

int SocketServer::markListening()
{
    return listen(listeningSocket, SOMAXCONN);
}

int SocketServer::waitConnection()
{
    clientSocket = accept(listeningSocket, (sockaddr *)&clientIn, (socklen_t *)&clientSize);

}

void SocketServer::parseIncoming()
{
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    while (true)
    {
        memset(messageBuffer, 0, 4096);

        int bytesRecvd = recv(clientSocket, messageBuffer, 4096, 0);

        if (bytesRecvd == -1)
        {
            std::cerr << "Connection Issue" << std::endl;
            break;
        }

        if (bytesRecvd == 0)
        {
            std::cout << "Client Disconnected" << std::endl;
            break;
        }

        std::cout << "Received: " << std::string(messageBuffer, 0, bytesRecvd) << std::endl;

        send(clientSocket, messageBuffer, bytesRecvd+1, 0);
    }
}

void SocketServer::closeSocket(int socketIn)
{
    close(socketIn);
}

void SocketServer::stopServer()
{
}

SocketServer::~SocketServer()
{
}
