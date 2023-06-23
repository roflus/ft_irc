#include "../include/server.hpp"

Server::Server() : serverSocket(-1), connectedClients(0) {
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
    return;
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

        for (int i = 1; i <= MAX_CLIENTS; ++i){
            if (fds[i].fd != -1 && (fds[i].revents & POLLIN)) {
                receiveMessages(i, buffer);
            }
        }
    }
    stopServer();
    return ;
}

void Server::acceptClient(){
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
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
            //const char *welcomeMessage = "Hello, welcome to Rolf and Quilfort's Server! What is your Nickname?\n";
            //send(clientSocket, welcomeMessage, strlen(welcomeMessage), 0);
            sendWelcomeMessage();

            connectedClients++;
            break;
        }
    }
}

void Server::disconnectClient(int index){
    int currentSocket = fds[index].fd;
    // Client has closed the connection or an error occurred
    std::cout << "Client disconnected. Client socket descriptor: " << currentSocket << std::endl;
    close(currentSocket);
    fds[index].fd = -1; // Mark as unused
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
    connectedClients--;
    std::cout << "connectedClients: " << connectedClients << std::endl;

    if (connectedClients == 0) {
        stopServer();
        // Iets anders voor vinden, maar ik had geen zin meer in dit
        exit (0);
    }
}

void Server::receiveMessages(int index, char *buffer){
    // Check for activity on the client sockets (incoming data)
    int currentSocket = fds[index].fd;
    int bytesRead = recv(currentSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        disconnectClient(index);
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
                //std::cout << "New nickname set for client " << currentSocket << ": " << it->second << std::endl;
                send(clientSocket, "Welcome\n", 8, 0);
            } else {
                std::cout << "Received message from " << it->second << buffer << std::endl;
                checkCommands(currentSocket, buffer);
            }
        }
    }
}
