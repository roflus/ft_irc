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
# include "../Src/Commands/Commands.hpp"
# include "../include/Client.hpp"
# include "../include/Channel.hpp"
# include <exception>


# define MAX_CLIENTS    10
# define BUFFER_SIZE     1024

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

    public:
        Server(const std::string &port, const std::string &password);
        ~Server();

        /*
            GetUser
            AddUser
            RemoveUser

            GetChannel
            AddChannel
            RemoveChannel
        */
        Client* GetClient(int fd);
        Client* AddClient(int fd);
        void    RemoveClient(int fd);

        Channel* GetChannel(std::string channelName);
        Channel* AddChannel(std::string channelName);
        void     RemoveChannel(std::string channelName);
        
        in_port_t GetPort();
        bool      CheckPassword();

        bool    HandleData(Client &client);

        /* custom exeption maybe toch wel een namespace gebruiken dan kun je deze exception overal gebruiken*/
        class ServerException: public std::exception {
            private: const char* _message;
            public:
                ServerException(const char* message) : _message(message) {}
                const char *what() const throw() { return _message; }
        };

        void startServer();
        void stopServer();
        // Dit kan nu ook private? Maybe in de toekomst wel nodig in andere files
        void runServer();
        void acceptClient();
        void receiveMessages(Client &client);
        void disconnectClient(int index);

};
#endif