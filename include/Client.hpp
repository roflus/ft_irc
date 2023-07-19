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
    std::string                     _username;
    std::string                     _hostname;
    std::string                     _servername;
    std::string                     _realname;
    std::string                     _nickname;
    std::string                     _password;
    sockaddr_in                     _address;


    std::string                     _buffer;
    int                             _clientSocket;
    bool                            _isRegistered;
    bool                            _isModerator;

    std::deque<std::string>         _arguments;
    std::deque<std::string>         _sendMessage;
    const char*                     _message;

public:
    Client();
    ~Client();

    /* Getter methods */
    std::string 			        getUsername();
    std::string 			        getPassword();
    std::string 			        getNickname();
    bool                            getRegistrated();
    bool                            getIsModerator();
    std::string 			        getBuffer();
    sockaddr_in 			        *getSockaddr();
    int                             getSocket();
	std::string				        getKey();
    std::deque<std::string>         getArguments();
    std::string                     getMessage(bool newline);
    bool                            sendAll();
    /* Setter methods */
    void                            setUsername(const std::string &username);
    void                            setHostname(const std::string &hostname);
    void                            setServername(const std::string &servername);
    void                            setRealname(const std::string &realname);
    void                            setPassword(const std::string &password);
    void        					setNickname(const std::string &nickname);
    void        					setBuffer(const std::string &buffer);
    void        					setSocket(const int &clientSocket);
    void                            setRegistrated(bool isRegistered);
    void                            setIsModerator(const bool &isModerator);
    void                            setMessage(std::string message);
    bool                            HandleBuffer();
    void                            parseBuffer();

    bool                            checkSendMessage();
    std::string                     getSendMessage();
    void                            setSendMessage(const std::string &name, const std::string &channel, \
                                                    const std::string &input);
    void                            setErrorMessage(const std::string &error);
};

#endif