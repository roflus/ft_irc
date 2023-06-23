#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    char buffer[BUFFER_SIZE];

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
    if (listen(serverSocket, 2) < 0) {
        std::cerr << "Failed to listen for client connections." << std::endl;
        return 1;
    }

    std::cout << "Server started. Listening on port " << PORT << std::endl;

    // Accept client connection
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept client connection." << std::endl;
        return 1;
    }

    std::cout << "Client connected. IP address: " << inet_ntoa(clientAddress.sin_addr) << std::endl;

    // Receive and send data to the client
    while (true) {
        memset(buffer, 0, sizeof(buffer));

        // Receive data from the client
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            // Client disconnected or error occurred
            std::cerr << "Client disconnected or error occurred." << std::endl;
            break;
        }
        std::string receivedMessage(buffer);
        std::string checkCommand = "KICK";
        int len = checkCommand.length();
        std::string test = receivedMessage.substr(0,len);
        std::cout << "Received message from client: " << receivedMessage << std::endl;
        if (strcmp(test.c_str(), checkCommand.c_str()) == 0) {

            // Send a custom message to the client
            const char* message = "You are the ball\n";
            send(clientSocket, message, strlen(message), 0);
        }
        else
            // Echo the received data back to the client
            send(clientSocket, buffer, bytesRead, 0);
    }

    // Close the client socket
    close(clientSocket);

    // Close the server socket
    close(serverSocket);

    return 0;
}

