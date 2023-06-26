#include "../include/Server.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
        return EXIT_FAILURE;
    Server irc(argv[1], argv[2]);
    
    irc.startServer();
    return 0;
}