# include "../../include/Client.hpp"

Client::Client()
    : _username(""),
      _hostname(""),
      _servername(""),
      _realname(""),
      _nickname(""),
      _password(""),
      _address(),
      _clientSocket(0),
      _isRegistered(false),
      _message("")
{}

Client::~Client() {
  close(this->_clientSocket);
}

/* Getters*/
std::string					Client::getUsername() { return this->_username; }
std::string					Client::getPassword() { return this->_password; }
std::string 				Client::getNickname() { return this->_nickname; }
bool        				Client::getRegistrated() { return this->_isRegistered; }
bool        				Client::getIsModerator() {return this->_isModerator;}
std::string 				Client::getBuffer() {return this->_buffer; }
int         				Client::getSocket() { return this->_clientSocket; }
sockaddr_in*				Client::getSockaddr() { return &_address; }
std::deque<std::string>		Client::getArguments() {return this->_arguments;}

/*Setters*/
void	Client::setUsername(const std::string &username) { this->_username = username; }
void    Client::setHostname(const std::string &hostname) { this->_hostname = hostname; }
void    Client::setServername(const std::string &servername) { this->_servername = servername; }
void    Client::setRealname(const std::string &realname) { this->_realname = realname; }

void    Client::setPassword(const std::string &password) { this->_password = password; }
void    Client::setNickname(const std::string &nickname) { this->_nickname = nickname; }
void    Client::setRegistrated(bool isRegistered) { this->_isRegistered = isRegistered; }
void    Client::setBuffer(const std::string &buffer) { this->_buffer = buffer; }
void    Client::setSocket(const int &clientSocket) { this->_clientSocket = clientSocket; }
void    Client::setIsModerator(const bool &isModerator) { this->_isModerator = isModerator; }
