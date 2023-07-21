# include "../../include/Client.hpp"

std::string Client::getMessage(bool newline) {
    std::string stringMessage;
    std::deque<std::string>::const_iterator it;
    for (it = _arguments.begin(); it != _arguments.end(); ++it) {
        stringMessage += *it;
        stringMessage += " ";
    }
    if (newline == true)
        stringMessage += "\n";
    return stringMessage;
}

std::string Client::getKey(){
    std::string key;
    if (_arguments.empty())
        return key;
    if (!_arguments.empty())
        key = _arguments.front();
    _arguments.pop_front();
    return key;
}

void       Client::parseBuffer() {
    size_t pos = this->_buffer.find("\r\n");
    if (pos == std::string::npos)
        throw ClientException("no \r\n in buffer");
    std::string tempbuffer = this->_buffer.substr(0, pos);
    std::istringstream stream(tempbuffer);
    std::string word;
    _arguments.clear();
    while (stream >> word)
        _arguments.push_back(word);
    this->_buffer.erase(0, pos + 2);
}

bool        Client::HandleBuffer() {
    char buffer[BUFFER_SIZE];

    //buffer nog checken voor \r\n ??
    if (this->_buffer.find("\r\n") == std::string::npos) {
        int bytesRead = recv(getSocket(), buffer, BUFFER_SIZE - 1, 0);
        std::cout << "wtf: " << bytesRead << std::endl;
        if (bytesRead == -1 && errno == EAGAIN) {
            errno = 0;
            return false;
        }
        if (bytesRead == -1)
            throw ClientException("Recv error, no Errno == EAGAIN");
        if (bytesRead == 0)
            throw ClientException("Error: client disconnected");
        buffer[bytesRead] = '\0';
        this->_buffer += buffer;
        std::cout << "buffer -> " << buffer << std::endl;
        std::cout << "this->buffer -> " << this->_buffer << std::endl;
    }
    bool print = this->_buffer.find("\r\n") != std::string::npos;
    std::cout << "return value: " << print << std::endl;
    return this->_buffer.find("\r\n") != std::string::npos;
}

bool        Client::checkSendMessage() {
    if (_sendMessage.empty())
        return false;
    return true;
}

std::string Client::getSendMessage(){
    std::string message;
    message = _sendMessage.front();
    _sendMessage.pop_front();
    return (message);
}

bool    Client::sendAll() {
    std::string message;
    while (_sendMessage.size()) {
        message = _sendMessage.front();
        send(getSocket(), message.c_str(), message.length(), 0);
        //error handling;
        _sendMessage.pop_front();
        message.erase();
    }
    return true;
}

void    Client::setMessage(std::string message) { _sendMessage.push_back(message + "\r\n"); }