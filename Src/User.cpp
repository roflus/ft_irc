# include "User.hpp"

User::User(/* args */)
{
}

User::~User()
{
}

// to add user with their info to the std::map with all the users. Zodat alle users en hun info bij elkaar staan
void User::registerUser(const std::string &username, const std::string &password, const std::string &nickname)
{
    User newUser;
    newUser.setUsername(username);
    newUser.setPassword(password);
    newUser.setNickname(nickname);
    users.insert(std::make_pair(username, newUser));
}

std::string User::getUsername() {
    return this->_username;
}
std::string User::getPassword() {
    return this->_password;
}
std::string User::getNickname() {
    return this->_nickname;
}
void        User::setUsername(const std::string &username) {
    this->_username = username;
}
void        User::setPassword(const std::string &password) {
    this->_password = password;
}
void        User::setNickname(const std::string &nickname) {
    this->_nickname = nickname;
}
