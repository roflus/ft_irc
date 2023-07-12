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
# include "Commands.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include <exception>


# define MAX_CLIENTS    10
# define BUFFER_SIZE    1024

class CheckCommands;

class Server {

    private:
        /* Map met clientsocket fd als key en User class als value */
        /* Map met alle Channels als value met de naam als key*/
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
        void                            removeClient(Client *client);

        Client*                         GetClient(int fd);
        void                            AddClient(int fd);

        Channel*                        getChannel(std::string channelName);
        Channel*                        AddChannel(std::string channelName);
        void                            RemoveChannel(std::string channelName);

        std::string                     getPassword();
        bool                            CheckPassword();

        in_port_t                       GetPort();

        bool                            HandleData(Client &client);
        void                            HandleInput(Client &client);
        void                            HandleOutput(Client &client, int i);
        void                            ReviewPoll();

        /* custom exeption maybe toch wel een namespace gebruiken dan kun je deze exception overal gebruiken*/
        class ServerException: public std::exception {
            private: const char* _message;
            public:
                ServerException(const char* message) : _message(message) {}
                const char *what() const throw() { return _message; }
        };

        void                            startServer();
        void                            stopServer();
        void                            runServer();
        void                            acceptClient();
        void                            receiveMessages(Client &client);
        void                            disconnectClient(int index);

};
#endif