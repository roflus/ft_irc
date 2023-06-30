#include "../../../include/Commands.hpp"

Nick::Nick(Server& server) : Commands(server)
{
}

Nick::~Nick()
{
}

void  Nick::execute(Client &client)
{
    // NICKNAME NU NOG ZONDER SPATIE
    
    std::string nickname(client.getKey());
    std::cout << "std::string: " << nickname << std::endl;
    std::cout << "Client nickname was: " << client.getNickname() << std::endl;
    client.setNickname(nickname);
    std::cout << "New Nickname is : " << client.getNickname() << std::endl;
} 