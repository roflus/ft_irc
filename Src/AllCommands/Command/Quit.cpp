#include "../../../include/Commands.hpp"

Quit::Quit(Server& server) : Commands(server) {}

Quit::~Quit() {}

void  Quit::execute(Client &client) {
    close(client.getSocket());
    exit(0);
} 