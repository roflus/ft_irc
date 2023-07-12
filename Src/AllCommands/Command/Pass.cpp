#include "../../../include/Commands.hpp"

Pass::Pass(Server& server) : Commands(server) {}

Pass::~Pass() {}

void  Pass::execute(Client &client) {
    std::string password = client.getKey();
    if (password.empty()) {
        if (client.getRegistrated()) {
            client.setErrorMessage("Password cannot be empty.\n");
        }
        else {
            std::string message = "Password cannot be empty.\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
        return ;
    }
    client.setPassword(password);
} 