#include "../../include/Server.hpp"

Client *Server::GetClient(int fd) {
    std::map<int, Client*>::iterator it = _clients.find(fd);
    if (it != _clients.end())
        return it->second;
    else
        throw ServerException("Client not found");
}

Client*	Server::getClientNickname(std::string nickname)
{
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