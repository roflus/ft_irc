#include "../../../include/Commands.hpp"

Nick::Nick(Server& server) : Commands(server) {}

Nick::~Nick() {}

void  Nick::execute(Client &client)
{
    // NICKNAME NU NOG ZONDER SPATIE
    // Username mag dan ook niet beginne met #
    std::string nickname(client.getKey());
    if (nickname[0] == '#') {
        client.setErrorMessage("Nickname cannot start with a '#'.\n");
        return ;
    }
    client.setNickname(nickname);
    std::string message = "Your new nickname is: " + client.getNickname() +".\n";
    client.setSendMessage("SYSTEM", "", message);
} 