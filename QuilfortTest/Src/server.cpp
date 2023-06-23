#include "../include/irc.hpp"

const int PORT = 8080;
const int MAX_CLIENTS = 10;
const int BUFFER_SIZE = 1024;

int testserver() {
    std::vector<std::pair<int, std::string> > clientSockets;
    struct pollfd fds[MAX_CLIENTS + 1]; // Additional 1 for server socket
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char buffer[BUFFER_SIZE];

    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create server socket." << std::endl;
        return 1;
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT); // Replace PORT with your desired port number

    // Bind server socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind server socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        std::cerr << "Failed to listen for connections." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server started. Waiting for connections..." << std::endl;

    // Add server socket to the pollfd array
    fds[0].fd = serverSocket;
    fds[0].events = POLLIN;

    // Initialize client sockets in the pollfd array
    for (int i = 1; i <= MAX_CLIENTS; ++i) {
        fds[i].fd = -1; // Mark as unused
    }

    while (true) {
        // Use poll to wait for activity on any of the connected sockets
        if (poll(fds, MAX_CLIENTS + 1, -1) == -1) {
            std::cerr << "Failed to poll." << std::endl;
            close(serverSocket);
            return 1;
        }

        // Check for activity on the server socket (new connection request)
        if (fds[0].revents & POLLIN) {
            socklen_t clientAddressSize = sizeof(clientAddress);

            // Accept the new client connection
            clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
            if (clientSocket == -1) {
                std::cerr << "Failed to accept client connection." << std::endl;
                close(serverSocket);
                return 1;
            }
            std::cout << "New client connected. Client socket descriptor: " << clientSocket << std::endl;

            // Add the new client socket to the pollfd array
            for (int i = 1; i <= MAX_CLIENTS; ++i) {
                if (fds[i].fd == -1) {
                    fds[i].fd = clientSocket;
                    fds[i].events = POLLIN;
                    clientSockets.push_back(std::make_pair(clientSocket, ""));
                    break;
                }
            }
        }

        // Check for activity on the client sockets (incoming data)
        for (int i = 1; i <= MAX_CLIENTS; ++i) {
            if (fds[i].fd != -1 && (fds[i].revents & POLLIN)) {
                int currentSocket = fds[i].fd;

                // Receive data from the client
                int bytesRead = recv(currentSocket, buffer, BUFFER_SIZE, 0);
                if (bytesRead <= 0) {
                    // Client has closed the connection or an error occurred
                    std::cout << "Client disconnected. Client socket descriptor: " << currentSocket << std::endl;
                    close(currentSocket);
                    fds[i].fd = -1; // Mark as unused

                    // Find the client in the vector
                    std::vector<std::pair<int, std::string> >::iterator it;
                    for (it = clientSockets.begin(); it != clientSockets.end(); ++it) {
                        if (it->first == currentSocket) {
                            break;
                        }
                    }
                    if (it != clientSockets.end()) {
                        clientSockets.erase(it);
                    }
                } else {
                    std::vector<std::pair<int, std::string> >::iterator it;
                    for (it = clientSockets.begin(); it != clientSockets.end(); ++it) {
                        if (it->first == currentSocket) {
                            break;
                        }
                    }
                    if (it != clientSockets.end()) {
                        if (it->second.empty()) {
                            // First message from the client is assumed to be the nickname
                            it->second = buffer;
                            std::cout << "New nickname set for client " << currentSocket << ": " << it->second << std::endl;
                        } else {
                            std::string receivedMessage(buffer);
                            std::string checkCommand = "KICK";
                            int len = checkCommand.length();
                            std::string test = receivedMessage.substr(0, len);
                            std::cout << "Received message from " << it->second << ": " << buffer << std::endl;
                            if (test == checkCommand) {
                                const char *message = "You are the ball\n";
                                send(currentSocket, message, strlen(message), 0);
                            } else {
                                send(currentSocket, buffer, bytesRead, 0);
                            }
                        }
                    }
                }
            }
        }
    }

    close(serverSocket);
    return 0;
}