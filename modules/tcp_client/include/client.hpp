#ifndef NETWORKCLIENT_HPP
#define NETWORKCLIENT_HPP

#include <windows.h>
#include <string>

namespace MyNetwork {

class NetworkClient {

public:
    NetworkClient( const std::string & serverAddress, uint16_t port );
    ~NetworkClient();

    bool        openConnection();
    bool        sendData( std::string & data );
    std::string recvData( int bufferSize );

private:
    std::string serverAddress;
    uint16_t    port;
    SOCKET      connectSocket;
    WSADATA     wsaData;

    void closeConnection();
};

} 

#endif
