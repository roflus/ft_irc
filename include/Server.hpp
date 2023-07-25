#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstring>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <thread>
# include <vector>
# include <poll.h>
# include <map>
# include <deque>
# include <fcntl.h>
# include <exception>
# include "Commands.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Replies.hpp"
# include "Errors.hpp"

# define MAX_CLIENTS    10
# define BUFFER_SIZE    1024

class CheckCommands;

class Server {

    private:
        std::map<int, Client*>          _clients;
        std::map<std::string, Channel*> _channels;
        std::vector<pollfd>             _pollfds;

        const in_port_t                 _port;
        const std::string               _password;
        int                             _serverSocket;

        CheckCommands*                  _checkCommands;

    public:
        Server(const std::string &port, const std::string &password);
        ~Server();

        Client*                         getClientNickname(std::string nickname);
        Client*	                        getClientUsername(std::string username); 
        Client*                         GetClient(int fd);
        void                            removeClient(Client *client);

        Channel*                        getChannel(std::string channelName);
        Channel*                        AddChannel(std::string channelName);
        void                            RemoveChannel(std::string channelName);

        std::string                     getPassword();

        void                            HandleInput(Client &client);
        void                            HandleOutput(Client &client, int i);
        void                            ReviewPoll();

        void                            startServer();
        void                            stopServer();
        void                            runServer();
        void                            acceptClient();
        void                            receiveMessages(Client &client);

        class ServerException: public std::exception {
            private: const char* _message;
            public:
                ServerException(const char* message) : _message(message) {}
                const char *what() const throw() { return _message; }
        };
};
#endif