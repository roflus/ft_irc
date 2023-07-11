#include "../../include/Server.hpp"

Client *Server::GetClient(int fd) {
    std::map<int, Client*>::iterator it = _clients.find(fd);
    if (it != _clients.end())
        return it->second;
    else
        throw ServerException("Client not found");
}

Client*	Server::getClientNickname(std::string nickname) {
    // MISSING ERROR CHECKS
    
    std::map<int, Client*>::iterator it;
	it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second->getNickname() == nickname)
			return it->second;
		++it;
	}
	return NULL;
}

void Server::acceptClient() {
    /* hier een nieuwe Client class aanmaken de socket naar accept zetten en dan in die map zetten */
    Client *client;
    client = new Client;
    socklen_t clientAddressSize = sizeof(client->getSockaddr());
    client->setSocket(accept(_serverSocket, (sockaddr *)client->getSockaddr(), &clientAddressSize));
    if (client->getSocket() == -1)
        throw ServerException("Failed to listen server socket");

    pollfd clientPollfd;
    clientPollfd.fd = client->getSocket();
    clientPollfd.events = POLLIN;
    _pollfds.push_back(clientPollfd);
    
    _clients[client->getSocket()] = client;
    std::string message = "Welcome! Give NICKname and PASSword\n";
    send(client->getSocket(), message.c_str(), message.size(), 0);
}

void    Server::removeClient(Client *client) {
    /*
        Client uit de pollfd halen.
        Client out lijst halen in server.
        Door lijst channels heen gaan en checken voor de client.
        zit client erin, remove client.
    */

    for (std::vector<pollfd>::iterator it = _pollfds.begin(); it != _pollfds.end(); ++it){
        if (it->fd == client->getSocket())
            _pollfds.erase(it);
    }
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (it->first == client->getSocket())
            _clients.erase(it);
    }
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        it->second->removeUser(*client);
    }
}
