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
    if (flag.size() == 2){
        if (flag[0] == '+') {
            if (flag[1] == 'i')
                targetChannel->setInviteOnly(true);
            else if (flag[1] == 't')
                targetChannel->setTopicIsForMod(true);
            else if (flag[1] == 'k') {
                std::string password = client.getKey();
                if (!password.empty())
                    targetChannel->setPassword(password);
                else
                    client.setErrorMessage("No password given\n");
            }
            else if (flag[1] == 'o') {
                Client *targetClient = _server.getClientNickname(client.getKey());
                if (targetClient != NULL) {
                    if (!targetChannel->isUserModerator(*targetClient)) {
                        targetChannel->addModerator(*targetClient);
                        targetClient->setSendMessage("SYSTEM",targetChannel->getName(), "You have been made moderator of this channel\n");
                    } else
                        client.setErrorMessage("User is already moderator\n");
                }
                else
                    client.setErrorMessage("User is not available, try again\n");
            }
            else if (flag[1] == 'l') {
                std::string limitString = client.getKey();
                for (char c : limitString) {
                    if (!std::isdigit(c)) {
                        client.setErrorMessage("Argument for userlimit must be a number.\n");
                        return ;
                    }
                }
                int limit = atoi(limitString.c_str());
                targetChannel->setUserLimit(limit);
            }
        } else if (flag[0] == '-') {
            if (flag[1] == 'i')
                targetChannel->setInviteOnly(false);
            else if (flag[1] == 't')
                targetChannel->setTopicIsForMod(false);
            else if (flag[1] == 'k') 
                targetChannel->setPassword("");
            else if (flag[1] == 'o') {
                Client *targetClient = _server.getClientNickname(client.getKey());
                if (targetClient != NULL) {
                    if (targetChannel->isUserModerator(*targetClient)) {
                        targetChannel->removeModerator(*targetClient);
                        targetClient->setSendMessage("SYSTEM", targetChannel->getName(), "You have been removed as moderator of this channel\n");
                    } else
                        client.setErrorMessage("User is not moderator\n");
                } else
                    client.setErrorMessage("User is not available, try again\n");
            }
            else if (flag[1] == 'l')
                targetChannel->setUserLimit(0);
        }
    } else
        client.setErrorMessage("Select the right flag\n");
}

void Mode::execute(Client &client)
{
    std::string target(client.getKey());
    if (target[0] == '#')
    {
        Channel *targetChannel;
        targetChannel = _server.getChannel(target);
        if (!targetChannel) {
            client.setErrorMessage("Channel does not exist \n");
            return;
        }
        else if (targetChannel->isUserModerator(client))
            accessChannel(client, target);
        else
            client.setErrorMessage("You are not the moderator\n");
    }
    else
        client.setErrorMessage("Channel name needs to start with a '#' \n");
}