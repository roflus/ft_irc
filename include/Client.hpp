#include <iostream>
#include <map>

class Client
{
private:
    std::string _username;
    std::string _nickname;
    std::string _password;

    bool        _isRegistered;

public:
    Client(/* args */);
    ~Client();

    std::string getUsername();
    std::string getPassword();
    std::string getNickname();
    void        setUsername(const std::string &username);
    void        setPassword(const std::string &password);
    void        setNickname(const std::string &nickname);

};
