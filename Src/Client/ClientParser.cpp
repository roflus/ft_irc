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

void        Client::parseBuffer() {
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

// void        Client::setSendMessage(const std::string &name, const std::string &channel, \
//                                     const std::string &input){
//     std::string message;
//     if (channel == "")
//         message = name + ": " + input;
//     else
//         message = "Channel: " + channel + " | " + name + \
//                     ": " + input;
//     _sendMessage.push_back(message);
// }

// void		Client::setErrorMessage(const std::string &error) {
// 		setSendMessage("SYSTEM", "", error);
// }

//bool        Client::HandleBuffer() {
//    char buffer[BUFFER_SIZE];
//    setBuffer("");
//    while (true) {
//        memset(buffer, 0, sizeof(buffer));
//        int bytesRead = recv(getSocket(), buffer, BUFFER_SIZE, 0);
//        if (bytesRead <= 0)
//            return false;
//        buffer[bytesRead] = '\0';
//        this->_buffer += buffer;
//        if (this->_buffer.find("\r\n") == std::string::npos)
//            break;
//    }
//    parseBuffer();
//    return true;
//}