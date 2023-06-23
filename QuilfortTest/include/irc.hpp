#ifndef IRC_HPP
# define IRC_HPP

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

    private:


    public:
        int testserver();



};



#endif