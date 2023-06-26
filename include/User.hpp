#include <iostream>
#include <map>

class User
{
private:
    std::string _username;
    std::string _nickname;
    std::string _password;
    std::map<std::string, User> users;

public:
    User(/* args */);
    ~User();


    void registerUser(const std::string &username, const std::string &password, const std::string &nickname);

    std::string getUsername();
    std::string getPassword();
    std::string getNickname();
    void        setUsername(const std::string &username);
    void        setPassword(const std::string &password);
    void        setNickname(const std::string &nickname);

};
