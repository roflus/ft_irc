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

# define MAX_CLIENTS    10
# define BUFFER_SIZE     1024

class Server {

    public:
        Server(const std::string &port, const std::string &password);
        ~Server();

        void startServer();
        void stopServer();
        // Dit kan nu ook private? Maybe in de toekomst wel nodig in andere files
        void runServer();
        void acceptClient();
        void receiveMessages(int index, char *buffer);
        void disconnectClient(int index);

        void sendWelcomeMessage();
    private:
        // std::vector<std::pair<int, std::string> > clientSockets;
        std::map<int, std::string> clientSockets;
        struct pollfd fds[MAX_CLIENTS + 1];
        int serverSocket;
        int connectedClients;
        int clientSocket;
        const in_port_t _port;
        std::string _password;
        const char *message;
};
#endif