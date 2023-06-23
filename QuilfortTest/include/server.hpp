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

# define PORT           8080
# define MAX_CLIENTS    10
# define BUFFER_SIZE     1024

class Server {

    public:
        Server();
        ~Server();

        void startServer();
        void stopServer();
        // Dit kan nu ook private? Maybe in de toekomst wel nodig in andere files
        void runServer();
        void acceptClient();

    private: 
       std::vector<std::pair<int, std::string> > clientSockets;
       struct pollfd fds[MAX_CLIENTS + 1];
       int serverSocket;
       int connectedClients;
       int clientSocket;




};



#endif