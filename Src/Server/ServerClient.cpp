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