#include <client.hpp>
#include <iostream>

int main()
{

    std::string serverAddress = "192.168.55.49";
    uint16_t    serverPort    = 27015;

    MyNetwork::NetworkClient client( serverAddress, serverPort );

    if ( !client.openConnection() ) {
        std::cerr << "Failed to connect to the server." << "\n";
        return 1;
    }

    std::cout << "Connected to the server successfully." << "\n";

    std::string messageToSend = "Hello";
    if ( !client.sendData( messageToSend ) ) {
        std::cerr << "Failed to send data to the server." << "\n";
        return 1;
    }

    std::cout << "Sent message to server: " << messageToSend << "\n";

    std::string receivedMessage = client.recvData( MyNetwork::DEFAULT_BUFLEN );
    if ( !receivedMessage.empty() ) {
        std::cout << "Received message from server: " << receivedMessage << "\n";
    }

    client.closeConnection();

    std::cout << "Connection closed." << "\n";

    return 0;
}