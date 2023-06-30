# include "../../include/Client.hpp"

Client::Client()
    : _username(""),
      _nickname(""),
      _password(""),
      _address(),
      _clientSocket(0),
      _isRegistered(false)
{
}

Client::~Client()
{
}

/* Getters*/
std::string Client::getUsername() { return this->_username; }
std::string Client::getPassword() { return this->_password; }
std::string Client::getNickname() { return this->_nickname; }
std::string Client::getBuffer() {return this->_buffer; }
int         Client::getSocket() { return this->_clientSocket; }
sockaddr_in *Client::getSockaddr() { return &_address; }
std::deque<std::string> Client::getArguments() {return this->_arguments;}

//std::queue<std::string> Client::getArguments() {return this->_arguments;}

/*Setters*/
void        Client::setUsername(const std::string &username) { this->_username = username; }
void        Client::setPassword(const std::string &password) { this->_password = password; }
void        Client::setNickname(const std::string &nickname) { this->_nickname = nickname; }
void        Client::setBuffer(const std::string &buffer) { this->_buffer = buffer; }
void        Client::setSocket(const int &clientSocket) { this->_clientSocket = clientSocket; }

std::string Client::getKey() {

    // Find the key (Argument tot space)
    // Nog een check toevoegen if (!_arguments.empty())
    std::string fullString = _arguments.front();
    size_t space = fullString.find(' ');
    std::string key;
    if (space != std::string::npos)
        key = fullString.substr(0, space);
    else
        key = fullString;

    size_t pos = 0;
    while ((pos = _arguments.front().find(key, pos)) != std::string::npos) 
        _arguments.front().erase(pos, key.length() + 1);
    return key;
}

bool        Client::HandleBuffer() {
    char buffer[BUFFER_SIZE];

    //buffer nog checken voor \r\n ??
    setBuffer("");
    memset(buffer, 0, sizeof(buffer));
    int bytesRead = recv(getSocket(), buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0)
        return false;
    buffer[bytesRead] = '\0';
    this->_buffer += buffer;
    _arguments.clear();
    _arguments = parseBuffer();
    return true;
}

std::deque<std::string> Client::parseBuffer() {
    std::deque<std::string> deque;
    deque.push_back(this->_buffer);
    return deque;
}