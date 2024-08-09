#include <Windows.h>
#include <client.hpp>
#include <iostream>

MyNetwork::NetworkClient::NetworkClient( const std::string & serverAddress, uint16_t port ) :
    serverAddress( serverAddress ), port( port ), connectSocket( INVALID_SOCKET )
{
    // Initialize Winsock
    int result = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
    if ( result != NO_ERROR ) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        throw std::runtime_error( "WSAStartup failed" );
    }
}

MyNetwork::NetworkClient::~NetworkClient() { closeConnection(); }

bool MyNetwork::NetworkClient::openConnection()
{

    connectSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( connectSocket == INVALID_SOCKET ) {
        std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("192.168.55.49");
    clientService.sin_port = htons( port );

    int result = connect( connectSocket, (SOCKADDR *)&clientService, sizeof( clientService ) );
    if ( result == SOCKET_ERROR ) {
        std::cerr << "Connect function failed with error: " << WSAGetLastError() << std::endl;
        closeConnection();
        return false;
    }

    return true;
}

bool MyNetwork::NetworkClient::sendData( std::string & data )
{
    int result = send( connectSocket, data.c_str(), (int)data.length() + 1, 0 );
    if ( result == SOCKET_ERROR ) {
        std::cerr << "Send failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

std::string MyNetwork::NetworkClient::recvData( int bufferSize )
{
    std::string recvStr( bufferSize, '\0' );
    int         result = recv( connectSocket, &recvStr[0], bufferSize, 0 );

    if ( result > 0 ) {
        recvStr.resize( result );
        return recvStr;
    }
    else if ( result == 0 ) {
        std::cout << "Connection closed" << std::endl;
    }
    else {
        std::cerr << "Recv failed with error: " << WSAGetLastError() << std::endl;
    }

    return "";
}

void MyNetwork::NetworkClient::closeConnection()
{
    if ( connectSocket != INVALID_SOCKET ) {
        closesocket( connectSocket );
        connectSocket = INVALID_SOCKET;
    }
}