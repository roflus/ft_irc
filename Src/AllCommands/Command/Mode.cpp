#include "../../../include/Commands.hpp"

Mode::Mode(Server &server) : Commands(server)
{
}

Mode::~Mode()
{
}

void Mode::accessChannel(Client &client, std::string target)
{
    client.setSendMessage("SYSTEM", "", "MODE TEST WORKING\n");
    Channel *targetChannel;
    targetChannel = _server.getChannel(target);
    std::string flag(client.getKey());
    if (flag == "i")
        client.setSendMessage("SYSTEM", "", "FUNCTION FOR I\n");
    else if (flag == "t")
        client.setSendMessage("SYSTEM", "", "FUNCTION FOR T\n");
    else if (flag == "k")
        client.setSendMessage("SYSTEM", "", "FUNCTION FOR K\n");
    else if (flag == "o") {
        Client *targetClient = _server.getClientNickname(client.getKey());
        if (targetClient != NULL)
            targetChannel->changeModerator(client, *targetClient);
        else 
            client.setErrorMessage("User is not available, try again\n");
    }
    else
        client.setErrorMessage("Select the right flag\n");
}

void Mode::execute(Client &client)
{
    std::string target(client.getKey());
    if (target[0] == '#')
    {
        Channel *targetChannel;
        targetChannel = _server.getChannel(target);
        if (!targetChannel)
            client.setErrorMessage("Channel does not exist \n");
        else if (targetChannel->isUserModerator(client))
            accessChannel(client, target);
        else
            client.setErrorMessage("You are not the moderator\n");
    }
    else
        client.setErrorMessage("Channel name needs to start with a '#' \n");
}