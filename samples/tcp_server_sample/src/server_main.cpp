#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h> // Include the correct header for WinSock functions

#define DEFAULT_PORT   27015
#define DEFAULT_BUFLEN 512

int main()
{
    SOCKET             ListenSocket = INVALID_SOCKET;
    SOCKET             ClientSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;

    WSADATA wsaData;
    int     iResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
    if ( iResult != NO_ERROR ) {
        std::cerr << "WSAStartup function failed with error: " << iResult << std::endl;
        return 1;
    }

    ListenSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( ListenSocket == INVALID_SOCKET ) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return 1;
    }

    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port        = htons( DEFAULT_PORT );

    if ( bind( ListenSocket, (sockaddr *)&serverAddr, sizeof( serverAddr ) ) == SOCKET_ERROR ) {
        std::cerr << "Bind failed.\n";
        closesocket( ListenSocket );
        WSACleanup();
        return 1;
    }

    if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
        std::cerr << "Listen failed.\n";
        closesocket( ListenSocket );
        WSACleanup();
        return 1;
    }
    
    while ( true ) {
        ClientSocket = accept( ListenSocket, nullptr, nullptr );
        if ( ClientSocket == INVALID_SOCKET ) {
            std::cerr << "Accept failed.\n";
            closesocket( ListenSocket );
            WSACleanup();
            return 1;
        }

        // Step 6: Receive data into a std::string
        const size_t bufferSize = DEFAULT_BUFLEN; // Use size_t for buffer size
        std::string receivedData(bufferSize, '\0'); // Initialize string with buffer size

        int recvResult = recv(ClientSocket, &receivedData[0], static_cast<int>(bufferSize), 0);
        if (recvResult > 0) {
            receivedData.resize(recvResult); // Resize to actual length of received data
            std::cout << "Received message: " << receivedData << std::endl;

            std::string sendbuf = "World";
            if ( send( ClientSocket, sendbuf.c_str(), sendbuf.length() + 1, 0 ) == SOCKET_ERROR ) {
                std::cerr << "Send failed.\n";
            }
        } else if (recvResult == 0) {
            std::cout << "Connection closed gracefully" << std::endl;
        } else {
            std::cerr << "Recv failed: " << WSAGetLastError() << std::endl;
        }

        closesocket(ClientSocket); // Close client socket after handling
    }

    closesocket( ListenSocket );
    WSACleanup();

    return 0;
}
