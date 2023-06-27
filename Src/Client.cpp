# include "../include/Client.hpp"

Client::Client(/* args */)
{
}

Client::~Client()
{
}

std::string Client::getUsername() {
    return this->_username;
}
std::string Client::getPassword() {
    return this->_password;
}
std::string Client::getNickname() {
    return this->_nickname;
}
void        Client::setUsername(const std::string &username) {
    this->_username = username;
}
void        Client::setPassword(const std::string &password) {
    this->_password = password;
}
void        Client::setNickname(const std::string &nickname) {
    this->_nickname = nickname;
}
