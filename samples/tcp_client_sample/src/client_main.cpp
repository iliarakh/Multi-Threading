#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DEFAULT_BUFLEN 512

int main()
{
    auto * sendbuf = "Recieved";
    char   recvbuf[DEFAULT_BUFLEN];
    int    recvbuflen = DEFAULT_BUFLEN;

    // Opens winsock shared library
    WSADATA wsaData;
    int     iResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
    if ( iResult != NO_ERROR ) {
        wprintf( L"WSAStartup function failed with error: %d\n", iResult );
        return 1;
    }

    SOCKET ConnectSocket;
    ConnectSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( ConnectSocket == INVALID_SOCKET ) {
        wprintf( L"socket function failed with error: %ld\n", WSAGetLastError() );
        WSACleanup();
        return 1;
    }

    sockaddr_in clientService;
    clientService.sin_family      = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( "192.168.55.49" );
    clientService.sin_port        = htons( 27015 );

    iResult = connect( ConnectSocket, (SOCKADDR *)&clientService, sizeof( clientService ) );
    if ( iResult == SOCKET_ERROR ) {
        wprintf( L"connect function failed with error: %ld\n", WSAGetLastError() );
        iResult = closesocket( ConnectSocket );
        if ( iResult == SOCKET_ERROR )
            wprintf( L"closesocket function failed with error: %ld\n", WSAGetLastError() );
        WSACleanup();
        return 1;
    }
    std::cout << "Sending Hello...\n";

    iResult = send( ConnectSocket, sendbuf, (int)strlen( sendbuf ), MSG_OOB );
    if ( iResult == SOCKET_ERROR ) {
        wprintf( L"send failed with error: %d\n", WSAGetLastError() );
        closesocket( ConnectSocket );
        WSACleanup();
        return 1;
    }

    std::cout << sendbuf;

    do {

        iResult = recv( ConnectSocket, recvbuf, recvbuflen, 0 );
        if ( iResult > 0 )
            printf( "Bytes received: %d\n", iResult );
        else if ( iResult == 0 )
            printf( "Connection closed\n" );
        else
            printf( "recv failed: %d\n", WSAGetLastError() );

    } while ( iResult > 0 );

    do {

        iResult = recv( ConnectSocket, recvbuf, recvbuflen, 0 );
        if ( iResult > 0 )
            printf( "recieved: %d\n", iResult );
        else if ( iResult == 0 )
            printf( "Connection closed\n" );
        else
            printf( "closing client... %d\n", WSAGetLastError() );

    } while ( iResult > 0 );

    // std::string response;
    // std::cout << "recieved: " << response << "\n";

    // std::cout << "closing client...\n";

    closesocket( ConnectSocket );
    // Close winsock shared library
    WSACleanup();
}