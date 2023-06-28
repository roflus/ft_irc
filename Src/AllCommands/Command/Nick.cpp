#include "../../../include/Commands.hpp"

Nick::Nick(Server& server) : Commands(server)
{
}

Nick::~Nick()
{
}

void  Nick::execute(Client &client)
{
    
    // std::string nickname = client.getArguments().front();
    // client.getArguments().pop();
    // client.setNickname(nickname);
    // std::cout << "HELLO NOW Invite" << std::endl;
    // std::string message = "Nickname is set to " + nickname;
    // send(client.getSocket(), message.c_str(), message.size(), 0);
} 