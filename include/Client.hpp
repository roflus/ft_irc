#ifndef CLIENT_HPP
#define CLIENT_HPP

# include <iostream>
# include <map>
# include <netinet/in.h>
# include <queue>
# include <deque>
# include <sstream>

# define BUFFER_SIZE    1024

class Client
{
private:
    std::string _username;
    std::string _nickname;
    std::string _password;
    sockaddr_in _address;


    std::string _buffer;
    int         _clientSocket;
    bool        _isRegistered;

    std::deque<std::string> _arguments;

public:
    Client();
    ~Client();

    /* Getter methods */
    std::string 			getUsername();
    std::string 			getPassword();
    std::string 			getNickname();
    std::string 			getBuffer();
    sockaddr_in 			*getSockaddr();
    int                     getSocket();
	std::string				getKey();
    std::deque<std::string> getArguments();


    /* Setter methods */
    void                            setUsername(const std::string &username);
    void                            setPassword(const std::string &password);
    void        					setNickname(const std::string &nickname);
    void        					setBuffer(const std::string &buffer);
    void        					setSocket(const int &clientSocket);


    bool                            HandleBuffer();
    std::deque<std::string>         parseBuffer();

    // PUUR FOR TESTING
    const char *message;
};


#endif