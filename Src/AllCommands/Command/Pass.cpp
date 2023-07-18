#include "../../../include/Commands.hpp"

Pass::Pass(Server& server) : Commands(server) {}

Pass::~Pass() {}

void  Pass::execute(Client &client) {
    std::string password = client.getKey();
    if (password.empty()) {
        if (client.getRegistrated()) {
            client.setMessage(ERR_PASSWDMISMATCH(client.getUsername()));
        }
        else {
            std::string message = ERR_PASSWDMISMATCH(client.getUsername());
            client.setMessage(message);
        }
        return ;
    }
    client.setPassword(password);
}