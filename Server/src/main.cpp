#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

int main()
{
    //TODO CREATE CLASS
    
    // Create socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "Can't Create Socket" << std::endl;
        return -1;
    }

    // Bind socket to IP / port
    std::string socket = std::getenv("server_socket");
    if (!socket.empty())
        std::cout << socket << std::endl;
    else
        std::cout << "Env variable 'SOCKET_SERVER' doesn't exist. Make sure it is set." << std::endl;

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(std::stoi(socket));
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
    {
        std::cerr << "Can't Bind To To Ip/Port" << std::endl;
        return -2;
    }

    // Mark socket for listening
    if (listen(listening, SOMAXCONN) == -1)
    {
        std::cerr << "Can't Listen" << std::endl;
        return -3;
    }

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);

    if (clientSocket == -1)
    {
        std::cerr << "Problem With Client Connecting" << std::endl;
        return -4;
    }

    // Close the listening socket
    close(listening);

    // while receiving - display message / echo
    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    char buf[4096];
    while (true)
    {
        memset(buf, 0, 4096);

        int bytesRecv = recv(clientSocket, buf, 4096, 0);

        if (bytesRecv == -1)
        {
            std::cerr << "Connection Issue" << std::endl;
            break;
        }

        if (bytesRecv == 0)
        {
            std::cout << "Client Disconnected" << std::endl;
            break;
        }

        std::cout << "Received: " << std::string(buf, 0, bytesRecv) << std::endl;

        send(clientSocket, buf, bytesRecv+1, 0);
    }

    // Close socket
    close(clientSocket);

    return 0;
};