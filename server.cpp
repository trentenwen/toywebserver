#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

int main()
{
    // step 1: init
    WSADATA wsaData;
    int wsaError;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaError = WSAStartup(wVersionRequested, &wsaData);
    if (wsaError != 0)
    {
        std::cout << "the Winsock2 dll not found" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "the status:" << wsaData.szSystemStatus << std::endl;
    }
    // step 2 - create
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cout << "error at socket()" << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "socket() is ok" << std::endl;
    }
    // step 3 - bind
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_port = htons(10086);
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    /*
    sockaddr_in, sockaddr can be converted to each other.
    sockaddr_in has a more clear data structure.
     */
    if (bind(serverSocket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR)
    {
        std::cout << "error at bind()" << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "bind() is ok" << std::endl;
    }
    // step 4 - listen
    if (listen(serverSocket, 1) != 0)
    {
        std::cout << "error at listen()" << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "listen() is ok, waiting for connections..." << std::endl;
    }
    // step 5 - accept
    /*
    accept is a block function
    it will return a duplicated socket, as the descriptor for connection to the client
     */
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        std::cout << "accept() failed" << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }
    std::cout << "accepted connection" << std::endl;
    // step 6 - receive data via TCP, from a connected socket (descriptor)!
    char receiveBuffer[200];
    int byteCount = recv(acceptSocket, receiveBuffer, 200, 0);
    if (byteCount < 0)
    {
        std::cout << "recv() error " << WSAGetLastError() << std::endl;
        return 0;
    }
    else
    {
        std::cout << "received ---" << receiveBuffer << "---" << std::endl;
    }

    system("pause");
    WSACleanup();
}