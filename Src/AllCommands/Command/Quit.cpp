#include "../../../include/Commands.hpp"

Quit::Quit(Server& server) : Commands(server)
{
}

Quit::~Quit()
{
}

void  Quit::execute(Client &client)
{
    /*
        _server.disconect client;
        opzoek welke client, en welk fd
        close fd.
        remove van de list en ook van alle channels??
    */
    close(client.getSocket());
    exit(0);
} 