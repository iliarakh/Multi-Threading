#include <server.hpp> 
#include <iostream>

int main() {
    
    MyServer::NetworkServer server;

    // start server
    if (!server.startServer()) {
        std::cerr << "Failed to start the server." << "\n";
        return 1; // exit with error code if server failed to start
    }

    std::cout << "Server started successfully. Waiting for connections..." << "\n";

    // run server to handle client connections
    server.run();

    std::cout << "Server shutting down." << "\n";
    return 0; // exit 
}
