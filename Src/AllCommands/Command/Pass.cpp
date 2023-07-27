#include "../../../include/Commands.hpp"

Pass::Pass(Server& server) : Commands(server) {}

Pass::~Pass() {}

void  Pass::execute(Client &client) {
    std::string password = client.getKey();
    client.setPassword(password);
}