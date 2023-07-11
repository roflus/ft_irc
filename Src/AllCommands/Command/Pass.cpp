#include "../../../include/Commands.hpp"

Pass::Pass(Server& server) : Commands(server)
{
}

Pass::~Pass()
{
}

void  Pass::execute(Client &client)
{
    std::string password = client.getKey();
    if (password.empty()) {
        client.setErrorMessage("Please provide a password.\n");
        return ;
    }
    client.setPassword(password);
} 