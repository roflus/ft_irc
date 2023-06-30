#include "../../../include/Commands.hpp"

Kick::Kick(Server& server) : Commands(server)
{
}

Kick::~Kick()
{
}

void  Kick::execute(Client &client)
{
    std::string arguments = client.getArguments().front() + '\n';
    std::cout << "HELLO NOW Invite" << std::endl;
    send(client.getSocket(), &arguments, arguments.length(), 0);
} 