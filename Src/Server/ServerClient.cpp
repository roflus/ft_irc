#include "../../include/Server.hpp"
  #include <fcntl.h>
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

Client*	Server::getClientUsername(std::string username) {
    // MISSING ERROR CHECKS
    std::map<int, Client*>::iterator it;
	it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second->getUsername() == username)
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
    fcntl(client->getSocket(), F_SETFL, O_NONBLOCK);
    std::cout << client->getSocket() << std::endl;
    // Setnonblocking(client->getSocket());
    pollfd clientPollfd;
    clientPollfd.fd = client->getSocket();
    clientPollfd.events = POLLIN | POLLHUP;
    // clientPollfd.revents = 0;
    _pollfds.push_back(clientPollfd);
    
    _clients[client->getSocket()] = client;
}

void    Server::removeClient(Client *client) {
    for (std::vector<pollfd>::iterator it = _pollfds.begin(); it != _pollfds.end(); ) {
        if (it->fd == client->getSocket()) 
            it = _pollfds.erase(it);
        else
            ++it;
    }
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end();) {
        if (it->first == client->getSocket())
            it = _clients.erase(it);
        else
            ++it;
    }
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        it->second->removeUser(*client);
    }
}
