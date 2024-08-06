#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string> // Include the string header

#define DEFAULT_BUFLEN 512

int main()
{
    std::string sendbuf = "Hello";
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return 1;
    }

    SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("192.168.55.49");
    clientService.sin_port = htons(27015);

    iResult = connect(ConnectSocket, (SOCKADDR *)&clientService, sizeof(clientService));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
        iResult = closesocket(ConnectSocket);
        if (iResult == SOCKET_ERROR)
            wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    std::cout << "Sending " << sendbuf << "...\n";

    iResult = send(ConnectSocket, sendbuf.c_str(), (int)sendbuf.length() + 1, MSG_OOB);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Use std::string for receiving data
    std::string recv_str(recvbuflen, '\0'); // Initialize with buffer size

    iResult = recv(ConnectSocket, &recv_str[0], recvbuflen, 0);
    if (iResult > 0) {
        recv_str.resize(iResult); // Resize to actual length of received data
        printf("Read %s\n", recv_str.c_str());
    } else if (iResult == 0) {
        printf("Connection closed\n");
    } else {
        printf("closing client... %d\n", WSAGetLastError());
    }

    closesocket(ConnectSocket);
    // Close winsock
    WSACleanup();
}
