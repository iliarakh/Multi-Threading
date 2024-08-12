#ifndef NETWORKCLIENT_HPP
#define NETWORKCLIENT_HPP

#include <string>
#include <windows.h>

namespace MyNetwork {

    constexpr int DEFAULT_BUFLEN = 512;

    class NetworkClient {

    public:
        NetworkClient( const std::string & serverAddress, uint16_t port );
        ~NetworkClient();

        bool        openConnection();
        bool        sendData( std::string & data );
        std::string recvData( int bufferSize );

        std::string serverAddress;
        uint16_t    port;
        SOCKET      connectSocket;
        WSADATA     wsaData;

        void closeConnection();
    };

}  // namespace MyNetwork

#endif
