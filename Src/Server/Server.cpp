#include "../../include/Server.hpp"
#include <fcntl.h>
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
    struct sockaddr_in serverAddress;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1)
        throw ServerException("Failed to create server socket");
    if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) == -1)
        throw ServerException("Failed to set nonblocking");

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(_port);
    if (bind(_serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
        throw ServerException("Failed to bind server socket");

    if (listen(_serverSocket, 1) == -1)
        throw ServerException("Failed to listen server socket");
    std::cout << "Server started with port number: " << _port << ". Waiting for connections..." << std::endl;

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
        if (poll(_pollfds.data(), _pollfds.size(), 0) == -1)
            throw ServerException("Failed to listen server socket");
        if (_pollfds[0].revents & POLLIN) {
            _pollfds[0].revents = 0;
            std::cout << "New Client Connected" << std::endl;
            acceptClient();
        }
        for (size_t i = 1; i < _pollfds.size(); i++) {
            client = GetClient(_pollfds[i].fd);

            if ((_pollfds[i]).revents & POLLHUP) {
                removeClient(client);
                continue;
            }

            if ((_pollfds[i].revents & POLLIN))
                HandleInput(*client);

            if ((_pollfds[i].revents & POLLOUT))
                HandleOutput(*client, i);

        }
        ReviewPoll();
    }
    stopServer();
    return ;
}

void Server::receiveMessages(Client &client) {
    std::map<int, Client*>::iterator it = _clients.find(client.getSocket());
    if (it != _clients.end())
        std::cout << "Received message from " << it->second->getNickname() \
            << std::endl << it->second->getBuffer() << std::endl;
}

void    Server::HandleInput(Client &client) {
    
    try {
        if (client.HandleBuffer() == false) {
            return;
        }
        receiveMessages(client);
        try {
            while (true){
                client.parseBuffer();
                _checkCommands->findCommand(client);
            }
        }
        catch (const std::exception& e) {
            // return ;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error" << e.what() << std::endl;      
        removeClient(&client);
    }
}

void    Server::HandleOutput(Client &client, int i) {
    try{
        if(client.sendAll()) {
            if (client.checkSendMessage() == false)
                _pollfds[i].events &= ~POLLOUT;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error" << e.what() << std::endl;
        removeClient(&client);
    }
}

void    Server::ReviewPoll() {
    Client *client;
    std::vector<pollfd>::iterator it = _pollfds.begin() + 1;
    while (it != _pollfds.end()) {
        client = GetClient(it->fd);
        if (client->checkSendMessage())
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