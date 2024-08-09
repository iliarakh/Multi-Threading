#include "server.hpp"
#include <Windows.h>
#include <iostream>

MyServer::NetworkServer::NetworkServer( uint16_t port ) : port( port ), ListenSocket( INVALID_SOCKET )
{
    WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
}

MyServer::NetworkServer::~NetworkServer()
{
    closeServer();
    WSACleanup();
}

bool MyServer::NetworkServer::startServer()
{
    ListenSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( ListenSocket == INVALID_SOCKET ) {
        std::cerr << "Socket creation failed.\n";
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port        = htons( port );

    if ( bind( ListenSocket, (sockaddr *)&serverAddr, sizeof( serverAddr ) ) == SOCKET_ERROR ) {
        std::cerr << "Bind failed.\n";
        closeServer();
        return false;
    }

    if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
        std::cerr << "Listen failed.\n";
        closeServer();
        return false;
    }

    return true;
}

void MyServer::NetworkServer::run()
{
    while ( true ) {
        SOCKET ClientSocket = accept( ListenSocket, nullptr, nullptr );
        if ( ClientSocket == INVALID_SOCKET ) {
            std::cerr << "Accept failed.\n";
            break;
        }

        handleClient( ClientSocket );
        closesocket( ClientSocket );
    }
}

void MyServer::NetworkServer::handleClient( SOCKET ClientSocket )
{
    const size_t bufferSize = DEFAULT_BUFLEN;       // Use size_t for buffer size
    std::string  receivedData( bufferSize, '\0' );  // Initialize string with buffer size

    int recvResult = recv( ClientSocket, &receivedData[0], static_cast< int >( bufferSize ), 0 );
    if ( recvResult > 0 ) {
        receivedData.resize( recvResult );  // Resize to actual length of received data
        std::cout << "Received message: " << receivedData << std::endl;

        std::string sendbuf = "World";
        if ( send( ClientSocket, sendbuf.c_str(), sendbuf.length() + 1, 0 ) == SOCKET_ERROR ) {
            std::cerr << "Send failed.\n";
        }
    }
    else if ( recvResult == 0 ) {
        std::cout << "Connection closed gracefully" << std::endl;
    }
    else {
        std::cerr << "Recv failed: " << WSAGetLastError() << std::endl;
    }
}

void MyServer::NetworkServer::closeServer()
{
    if ( ListenSocket != INVALID_SOCKET ) {
        closesocket( ListenSocket );
        ListenSocket = INVALID_SOCKET;
    }
}