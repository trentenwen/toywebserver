#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

int main()
{
    SOCKET clientSocket;
    // step 1 - init
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
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "error at socket()" << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "socket() is ok" << std::endl;
    }
    // step 3 - connect
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(10086);
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(clientSocket, (SOCKADDR *)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        std::cout << "Client: connect() is fail" << std::endl;
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "connect() is ok" << std::endl;
    }
    // step 4 - send data via TCP
    std::cout << "Enter your message " << std::endl;
    char buffer[200];
    std::cin.getline(buffer, 200);
    /*
    buffer is the pointer of data, it can be the pointer for an object
    char buffer[200] is interpreted as a pointer to the first element -> char*
    if data is an object, we need to do type convert, (char*)&object
     */
    int byteCount = send(clientSocket, buffer, 200, 0);
    if (byteCount == SOCKET_ERROR)
    {
        std::cout << "send() error " << WSAGetLastError() << std::endl;
    }
    else
    {
        std::cout << "sent " << byteCount << " bytes" << std::endl;
    }

    system("pause");
    WSACleanup();
}