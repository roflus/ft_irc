#include "../include/Server.hpp"

Server::Server(const std::string &port, const std::string &password) : 
    _serverSocket(-1), connectedClients(0),
    _port(atoi(port.c_str())), _password(password) {

    /* Bind listen dus server opstarten kan hier?
    Maaaar..... dan moeten we dus namespace doen, kan wel ? wat denk jij? is wel BigBrain 
    voor nu is het nog hetzelfde als eerst */

}

Server::~Server() {
    stopServer();
}

void Server::stopServer() {
    if (_serverSocket != -1) {
        close(_serverSocket);
        _serverSocket = -1;
    }

    // Close all client sockets
    for (int i = 0; i <= MAX_CLIENTS; ++i) {
        if (_pollfds[i].fd != -1) {
            close(_pollfds[i].fd);
            _pollfds[i].fd = -1;
        }
    }
    clientSockets.clear();
}

void Server::startServer() {
    struct sockaddr_in serverAddress, clientAddress;

    /* Create serversocket en throw exception en dan in de main opvangen met try en chatch want */
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1)
        throw ServerException("Failed to create server socket");

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(_port);

    // Bind server socket to the specified address and port
    if (bind(_serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
        throw ServerException("Failed to bind server socket");

    // Listen for incoming connections
    if (listen(_serverSocket, 1) == -1)
        throw ServerException("Failed to listen server socket");

    std::cout << "Server started with port number: " << _port << ". Waiting for connections..." << std::endl;

    // Add server socket to the pollfd vector
    pollfd serverPollfd;
    serverPollfd.fd = _serverSocket;
    serverPollfd.events = POLLIN;
    _pollfds.push_back(serverPollfd);
    // FUNCTION FOR RUNNING SERVER
    runServer();
    return;
}

void Server::runServer(){
    char buffer[BUFFER_SIZE];


    while (true) {
        memset(buffer, 0, sizeof(buffer));
        // Use poll to wait for activity on any of the connected sockets
        if (poll(_pollfds.data(), MAX_CLIENTS + 1, -1) == -1)
            throw ServerException("Failed to listen server socket");

        if (_pollfds[0].revents & POLLIN) {
            acceptClient();
        }
        for (int i = 1; i <= connectedClients; ++i){
            if (_pollfds[i].fd != -1 && (_pollfds[i].revents & POLLIN)) {
                receiveMessages(i, buffer);
            std::cout << "kom je hier" << std::endl;
            }
        }
    }
    stopServer();
    return ;
}

void Server::sendWelcomeMessage() {
    message = "Hello, welcome to Rolf and Quilfort's Server! What is your Nickname?\n";
    send(clientSocket, message, strlen(message), 0);
}

void Server::acceptClient(){
    /* hier een nieuwe Client class aanmaken de socket naar accept zetten en dan in die map zetten */

    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    clientSocket = accept(_serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
    if (clientSocket == -1)
        throw ServerException("Failed to listen server socket");

    pollfd clientPollfd;
    clientPollfd.fd = clientSocket;
    clientPollfd.events = POLLIN;
    _pollfds.push_back(clientPollfd);
    connectedClients++;
    // comment hieboven inplaats van dit
    clientSockets.insert(std::make_pair(clientSocket, ""));
    sendWelcomeMessage();
}

void Server::disconnectClient(int index){
    int currentSocket = _pollfds[index].fd;
    // Client has closed the connection or an error occurred
    std::cout << "Client disconnected. Client socket descriptor: " << currentSocket << std::endl;
    close(currentSocket);
    // _pollfds[index].fd = -1; // Mark as unused
    // Find the client in the vector
    std::map<int, std::string>::iterator it;
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
    Commands command;
    int currentSocket = _pollfds[index].fd;
    int bytesRead = recv(currentSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        disconnectClient(index);
    } else {
        std::map<int, std::string>::iterator it;
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
                command.checkCommands(currentSocket, buffer);
            }
        }
    }
}
