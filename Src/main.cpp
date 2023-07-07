#include "../include/Server.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Error: ";
        std::cerr << "Not enough arguments given: Port and Password" << std::endl;
        if (argc == 2)
            std::cerr << "Also need to add the password" << std::endl;
        return EXIT_FAILURE;
    }
    Server irc(argv[1], argv[2]);
    try
    {
        irc.startServer();
    }
    catch (const std::exception &ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}