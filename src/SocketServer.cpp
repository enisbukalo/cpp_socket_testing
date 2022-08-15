#include "SocketServer.h"

SocketServer::SocketServer()
{
    std::cout << "Socket Server Constructor" << std::endl;
    socketNumber.clear();
    char* ss = std::getenv("SERVER_SOCKET");
    socketNumber = (ss == nullptr) ? "" : ss;
    if (!socketNumber.empty()){
        std::cout << "Socket Number: " << socketNumber << std::endl;
    }
    else{
        std::cerr << "Env variable 'SOCKET_SERVER' doesn't exist. Make sure it is set." << std::endl; 
        exit(0);
    }
    std::cout << "End of server constr" << std::endl;
}

void SocketServer::startServer()
{
    int w = serverLoop();
}

int SocketServer::serverLoop()
{
    //TODO Handle Errors Coming Back As -1.
    //TODO Need to add in conditional Var for multi-Threaded comms?
    std::cout << "Starting Server Loop" << std::endl;
    listeningSocket = createSocket();
    int x = bindSocket();
    int y = markListening();
    clientSocket = waitConnection();
    close(listeningSocket);
    parseIncoming();
    close(clientSocket);
    return 0;
}

int SocketServer::createSocket()
{
    std::cout << "Creating Socket" << std::endl;
    return socket(AF_INET, SOCK_STREAM, 0);
}

int SocketServer::bindSocket()
{
    std::cout << "Binding Socket" << std::endl;

    hint.sin_family = AF_INET;
    hint.sin_port = htons(std::stoi(socketNumber));
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    return bind(listeningSocket, (sockaddr *)&hint, sizeof(hint));
}

int SocketServer::markListening()
{
    std::cout << "Marking Socket For Listening" << std::endl;
    return listen(listeningSocket, SOMAXCONN);
}

int SocketServer::waitConnection()
{
    std::cout << "Waiting For Connection In" << std::endl;
    return accept(listeningSocket, (sockaddr *)&clientIn, &clientSize);
}

void SocketServer::parseIncoming()
{
    std::cout << "Parsing Incoming Messages" << std::endl;
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
    std::cout << "Closing Socket" << std::endl;
    close(socketIn);
}

void SocketServer::stopServer()
{
    std::cout << "Stopping Server" << std::endl;
}

SocketServer::~SocketServer()
{
}
