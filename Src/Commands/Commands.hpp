#include <iostream>
#include <sys/socket.h>
class Commands
{
private:
    /* data */
public:
    Commands(/* args */);
    ~Commands();

    void  checkCommands(int currentSocket, char *buffer);
};


