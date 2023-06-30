# include "../../include/Client.hpp"

Client::Client()
    : _username(""),
      _nickname(""),
      _password(""),
      _address(),
      _clientSocket(0),
      _isRegistered(false),
      _message("")
{
}

Client::~Client()
{
}

/* Getters*/
std::string Client::getUsername() { return this->_username; }
std::string Client::getPassword() { return this->_password; }
std::string Client::getNickname() { return this->_nickname; }
bool        Client::getRegistrated() { return this->_isRegistered; }
std::string Client::getBuffer() {return this->_buffer; }
int         Client::getSocket() { return this->_clientSocket; }
sockaddr_in *Client::getSockaddr() { return &_address; }
std::deque<std::string> Client::getArguments() {return this->_arguments;}


const char* Client::getMessage(bool newline) {
    std::string stringMessage;
    std::deque<std::string>::const_iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        stringMessage += *it;
        stringMessage += " ";
    }
    if (newline == true)
        stringMessage += "\n";
    _message = stringMessage.c_str();
    return this->_message;
}

/*Setters*/
void        Client::setUsername(const std::string &username) { this->_username = username; }
void        Client::setPassword(const std::string &password) { this->_password = password; }
void        Client::setNickname(const std::string &nickname) { this->_nickname = nickname; }
void        Client::setRegistrated(bool isRegistered) { this->_isRegistered = isRegistered; }
void        Client::setBuffer(const std::string &buffer) { this->_buffer = buffer; }
void        Client::setSocket(const int &clientSocket) { this->_clientSocket = clientSocket; }

std::string Client::getKey(){
    // Find the key (Argument tot space)
    // Nog een check toevoegen if (!_arguments.empty() etc.)

    std::string key;
    if (!_arguments.empty())
        key = _arguments.front();
    _arguments.pop_front();
    return key;
}

void Client::parseBuffer() {
    std::istringstream stream(this->_buffer);
    std::string word;
    _arguments.clear();
    while (stream >> word)
        _arguments.push_back(word);
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
    parseBuffer();
    return true;
}

