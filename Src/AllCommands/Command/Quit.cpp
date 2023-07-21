#include "../../../include/Commands.hpp"

Quit::Quit(Server& server) : Commands(server) {}

Quit::~Quit() {}

void  Quit::execute(Client &client) {
    _server.removeClient(&client);
} 