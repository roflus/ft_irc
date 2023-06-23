#include "../include/server.hpp"

Server::Server() : serverSocket(-1) {
    // Init sockets in de poll array
    for (int i = 0; i <= MAX_CLIENTS; ++i) {
        fds[i].fd = -1;
    }
}

Server::~Server() {
    stopServer();
}

void Server::stopServer() {
    if (serverSocket != -1) {
        close(serverSocket);
        serverSocket = -1;
    }

    // Close all client sockets
    for (int i = 0; i <= MAX_CLIENTS; ++i) {
        if (fds[i].fd != -1) {
            close(fds[i].fd);
            fds[i].fd = -1;
        }
    }
    clientSockets.clear();
}

void Server::startServer() {
    struct sockaddr_in serverAddress, clientAddress;

    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create server socket." << std::endl;
        return;
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT); // Replace PORT with your desired port number

    // Bind server socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind server socket." << std::endl;
        close(serverSocket);
        return;
    }

    // Listen for incoming connections
    if (listen(serverSocket, MAX_CLIENTS) == -1) {
        std::cerr << "Failed to listen for connections." << std::endl;
        close(serverSocket);
        return;
    }

    std::cout << "Server started. Waiting for connections..." << std::endl;

    // Add server socket to the pollfd array
    fds[0].fd = serverSocket;
    fds[0].events = POLLIN;

    // FUNCTION FOR RUNNING SERVER
    runServer();
}

void Server::runServer(){
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        // Use poll to wait for activity on any of the connected sockets
        if (poll(fds, MAX_CLIENTS + 1, -1) == -1) {
            std::cerr << "Failed to poll." << std::endl;
            stopServer();
            return;
        }
        if (fds[0].revents & POLLIN) {
            acceptClient();
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

                    connectedClients--; // Decrement the counter

                    // Check if all clients have disconnected
                    if (connectedClients == 0) {
                        close(serverSocket);
                        return ;
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
                            send(clientSocket, "Welcome\n", 8, 0);
                        } else {
                            std::string receivedMessage(buffer);
                            std::string checkCommand = "KICK";
                            int len = checkCommand.length();
                            std::string test = receivedMessage.substr(0, len);
                            std::cout << "Received message from " << it->second << buffer;
                            if (test == checkCommand) {
                                const char *message = "You are the ball\n";
                                send(currentSocket, message, strlen(message), 0);
                            }
                        }
                    }
                }
            }
        }
    }
    close(serverSocket);
    return;
}

void Server::acceptClient(){
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    connectedClients = 0; // Counter for connected clients

    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
    if (clientSocket == -1) {
        std::cerr << "Failed to accept client connection." << std::endl;
        stopServer();
        return ;
    }

    // Add the new client socket to the pollfd array
    for (int i = 1; i <= MAX_CLIENTS; ++i) {
        if (fds[i].fd == -1) {
            fds[i].fd = clientSocket;
            fds[i].events = POLLIN;
            clientSockets.push_back(std::make_pair(clientSocket, ""));
            const char *welcomeMessage = "Hello, welcome to Rolf and Quilfort's Server! What is your Nickname?\n";
            send(clientSocket, welcomeMessage, strlen(welcomeMessage), 0);
            connectedClients++; // Increment the counter
            break;
        }
    }
}