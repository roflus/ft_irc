#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <list>
#include <poll.h>

const int PORT = 8080;
const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

int main() {
    int serverSocket;
    struct sockaddr_in serverAddress;

    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create server socket." << std::endl;
        return 1;
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Bind the server socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to bind server socket." << std::endl;
        return 1;
    }

    // Listen for client connections
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        std::cerr << "Failed to listen for client connections." << std::endl;
        return 1;
    }

    std::cout << "Server started. Listening on port " << PORT << std::endl;

    // Create a list to store client sockets
    std::list<int> clientSockets;

    // Create a pollfd structure for the server socket
    struct pollfd serverPollfd;
    serverPollfd.fd = serverSocket;
    serverPollfd.events = POLLIN;

    // Create a list of pollfd structures for client sockets
    std::list<pollfd> clientPollfds;

    while (true) {
        // Use poll() to wait for events on the server socket and client sockets
        int numReady = poll(&serverPollfd, 1 + clientPollfds.size(), -1);
        if (numReady < 0) {
            std::cerr << "Error occurred in poll()." << std::endl;
            break;
        }

        // Check if the server socket has an event
        if (serverPollfd.revents & POLLIN) {
            // Accept client connection
            struct sockaddr_in clientAddress;
            socklen_t clientAddressLength = sizeof(clientAddress);
            int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
            if (clientSocket < 0) {
                std::cerr << "Failed to accept client connection." << std::endl;
                break;
            }

            std::cout << "Client connected. IP address: " << inet_ntoa(clientAddress.sin_addr) << std::endl;

            // Add the client socket to the list of client sockets
            clientSockets.push_back(clientSocket);

            // Create a pollfd structure for the client socket
            struct pollfd clientPollfd;
            clientPollfd.fd = clientSocket;
            clientPollfd.events = POLLIN;

            // Add the client pollfd to the list of client pollfds
            clientPollfds.push_back(clientPollfd);
        }

        // Check events on client sockets
        for (auto it = clientPollfds.begin(); it != clientPollfds.end(); ) {
            if (it->revents & POLLIN) {
                char buffer[BUFFER_SIZE];
                memset(buffer, 0, sizeof(buffer));

                // Receive data from the client
                int bytesRead = recv(it->fd, buffer, sizeof(buffer) - 1, 0);
                if (bytesRead <= 0) {
                    // Client disconnected or error occurred
                    std::cerr << "Client disconnected or error occurred." << std::endl;

                    // Remove the client socket and pollfd from the lists
                    close(it->fd);
                    it = clientPollfds.erase(it);
                    clientSockets.erase(std::next(clientSockets.begin(), std::distance(clientPollfds.begin(), it)));
                    continue;
                }

                std::cout << "Received message from client: " << buffer << std::endl;

                // Echo the received data back to the client
                send(it->fd, buffer, bytesRead, 0);
            }

            ++it;
        }
    }

    // Close server socket
    close(serverSocket);

    return 0;
}