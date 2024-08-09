#ifndef NETWORKSERVER_HPP
#define NETWORKSERVER_HPP

#include <windows.h>
#include <string>

#define DEFAULT_PORT 27015
#define DEFAULT_BUFLEN 512

namespace MyServer {

class NetworkServer {
public:
    NetworkServer(uint16_t port = DEFAULT_PORT);
    ~NetworkServer();

    bool startServer();
    void run();

private:
    uint16_t port;
    SOCKET ListenSocket;
    WSADATA wsaData;

    void handleClient(SOCKET ClientSocket);
    void closeServer();
};
}
#endif // NETWORKSERVER_HPP
