#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>

#define DEFAULT_PORT   27015
#define DEFAULT_BUFLEN 512

int main()
{
    SOCKET             ListenSocket = INVALID_SOCKET;
    SOCKET             ClientSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;
    char               recvbuf[DEFAULT_BUFLEN];
    int                recvbuflen = DEFAULT_BUFLEN;

    WSADATA wsaData;
    int     iResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
    if ( iResult != NO_ERROR ) {
        wprintf( L"WSAStartup function failed with error: %d\n", iResult );
        return 1;
    }

    ListenSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( ListenSocket == INVALID_SOCKET ) {
        std::cout << "Socket creation failed.\n";
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

        if ( recv( ClientSocket, recvbuf, recvbuflen, 0 ) > 0 ) {
            std::cout << "Received: " << recvbuf << std::endl;

            std::string sendbuf = "World";
            if ( send( ClientSocket, sendbuf.c_str(), sendbuf.length() + 1, 0 ) == SOCKET_ERROR ) {
                std::cerr << "Send failed.\n";
            }
        }
        else {
            std::cerr << "Receive failed.\n";
        }
    }

    closesocket( ClientSocket );
    closesocket( ListenSocket );
    WSACleanup();

    return 0;
}
