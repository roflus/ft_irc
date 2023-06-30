#include "../../../include/Commands.hpp"

Pass::Pass(Server& server) : Commands(server)
{
}

Pass::~Pass()
{
}

void  Pass::execute(Client &client)
{
    // NICKNAME NU NOG ZONDER SPATIE
    
    std::string nickname(client.getKey());
    std::cout << "std::string: " << nickname << std::endl;
    std::cout << "Client nickname was: " << client.getNickname() << std::endl;
    client.setNickname(nickname);
    std::cout << "New Nickname is : " << client.getNickname() << std::endl;
} 