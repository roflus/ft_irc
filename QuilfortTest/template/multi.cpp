#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <vector>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

void handleClient(int clientSocket, const sockaddr_in& clientAddress) {
    char buffer[BUFFER_SIZE];
    std::cout << "Client connected. IP address: " << inet_ntoa(clientAddress.sin_addr) << std::endl;

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        // Receive data from the client
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            // Client disconnected or error occurred
            std::cerr << "Client disconnected or error occurred. IP address: " << inet_ntoa(clientAddress.sin_addr) << std::endl;
            break;
        }

        std::cout << "Received message from client. IP address: " << inet_ntoa(clientAddress.sin_addr) << ", Message: " << buffer << std::endl;

        // Echo the received data back to the client
        send(clientSocket, buffer, bytesRead, 0);
    }

    // Close the client socket
    close(clientSocket);
}

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
    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen for client connections." << std::endl;
        return 1;
    }

    std::cout << "Server started. Listening on port " << PORT << std::endl;

    std::vector<std::thread> clientThreads;

    while (true) {
        // Accept client connection
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection." << std::endl;
            continue;
        }

        // Start a new thread to handle the client
        std::thread thread(handleClient, clientSocket, std::ref(clientAddress));
        clientThreads.push_back(std::move(thread));
    }

    // Close all client threads
    for (auto& thread : clientThreads) {
        thread.join();
    }

    // Close the server socket
    close(serverSocket);

    return 0;
}
