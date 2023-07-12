#include "../../include/Server.hpp"

Server::Server(const std::string &port, const std::string &password) : 
    _serverSocket(-1),
    _port(atoi(port.c_str())), 
    _password(password),
    _checkCommands(new CheckCommands(*this))
    {}

Server::~Server() {
    delete _checkCommands;
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
        delete it->second;
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
        delete it->second;
    stopServer();
}

std::string Server::getPassword() { return this->_password; }

void Server::stopServer() {
    if (_serverSocket != -1) {
        close(_serverSocket);
        _serverSocket = -1;
    }

    // Close all client sockets
    for (std::vector<pollfd>::iterator it =_pollfds.begin(); it != _pollfds.end(); ++it) {
        if (it->fd >= 0)
            close(it->fd);
    }
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
    runServer();
    return;
}

void Server::runServer() {
    Client *client;
    while (true) {
        // Use poll to wait for activity on any of the connected sockets
        if (poll(_pollfds.data(), _pollfds.size(), -1) == -1)
            throw ServerException("Failed to listen server socket");
        system("leaks ircserv");
        if (_pollfds[0].revents & POLLIN) {
            std::cout << "New Client Connected" << std::endl;
            acceptClient();
        }
        for (int i = 1; i <= _clients.size(); ++i) {
            client = GetClient(_pollfds[i].fd);
            if (client->checkSendMessage() && client->getRegistrated() == true)
                _pollfds[i].events |= POLLOUT;

            if ((_pollfds[i]).revents & POLLHUP)
                removeClient(client);

            if ((_pollfds[i].revents & POLLIN))
                HandleInput(*client);

            if ((_pollfds[i].revents & POLLOUT) && client->checkSendMessage())
                HandleOutput(*client, i);
        }
        ReviewPoll();
    }
    stopServer();
    return ;
}

void Server::receiveMessages(Client &client) {
    // Check for activity on the client sockets (incoming data)
    std::map<int, Client*>::iterator it = _clients.find(client.getSocket());
    if (it != _clients.end())
        std::cout << "Received message from " << it->second->getNickname() \
            << std::endl << it->second->getBuffer() << std::endl;
}

void    Server::HandleInput(Client &client) {
    if (!client.HandleBuffer()) {
        removeClient(&client);
        return ;
    }
    receiveMessages(client);
    _checkCommands->findCommand(client);
}

void    Server::HandleOutput(Client &client, int i) {
    std::string message = client.getSendMessage();
    send(client.getSocket(), message.c_str(), message.length(), 0);
    // Remove POLLOUT als geen messages
    if (!client.checkSendMessage())
        _pollfds[i].events &= ~POLLOUT;
}

void    Server::ReviewPoll() {
    Client *client;
    std::vector<pollfd>::iterator it = _pollfds.begin() + 1;
    while (it != _pollfds.end()) {
        client = GetClient(it->fd);
        if (!client->checkSendMessage() && client->getRegistrated() == true)
            it->events |= POLLOUT;
        ++it;
    }
    it = this->_pollfds.begin() + 1;
    while (it != this->_pollfds.end()) {
        if (!it->events)
            it = this->_pollfds.erase(it);
        else
            it++;
    }
}
// void Server::disconnectClient(int index){
//     int currentSocket = _pollfds[index].fd;
//     // Client has closed the connection or an error occurred
//     std::cout << "Client disconnected. Client socket descriptor: " << currentSocket << std::endl;
//     close(currentSocket);
//     // _pollfds[index].fd = -1; // Mark as unused
//     // Find the client in the vector
//     std::map<int, std::string>::iterator it;
//     for (it = clientSockets.begin(); it != clientSockets.end(); ++it) {
//         if (it->first == currentSocket) {
//             break;

//         }
//     }
//     if (it != clientSockets.end()) {
//         clientSockets.erase(it);
//     }
//     std::cout << "connectedClients: " << connectedClients << std::endl;

//     if (connectedClients == 0) {
//         stopServer();
//         // Iets anders voor vinden, maar ik had geen zin meer in dit
//         exit (0);
//     }
// }

