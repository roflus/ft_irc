#include "../../../include/Commands.hpp"

Mode::Mode(Server &server) : Commands(server) {}

Mode::~Mode() {}

static bool addMode(Client &client, Channel &targetChannel, std::string flag, Server &server) {
    if (flag[1] == 'i')
        targetChannel.setInviteOnly(true);
    else if (flag[1] == 't')
        targetChannel.setTopicIsForMod(true);
    else if (flag[1] == 'k') {
        std::string password = client.getKey();
        if (!password.empty())
            targetChannel.setPassword(password, true);
        else {
            client.setMessage(ERR_PASSWDMISMATCH(client.getNickname()));
            return false;
        }
    }
    else if (flag[1] == 'o') {
        std::string nickname = client.getKey();
        Client *targetClient = server.getClientNickname(nickname);
        if (targetClient != NULL) {
            if (!targetChannel.isUserModerator(*targetClient))
                targetChannel.addModerator(*targetClient);
        }
        else {
            client.setMessage(ERR_NOSUCHNICK(nickname));
            return false;
        }
    }
    else if (flag[1] == 'l') {
        std::string limitString = client.getKey();
        for (int i = 0; i < limitString.size(); i++) {
            if (!std::isdigit(limitString[i])) {
                client.setMessage(":" + client.getNickname() +  " :Argument for userlimit must be a number.");
                return false;
            }
        }
        int limit = atoi(limitString.c_str());
        targetChannel.setUserLimit(limit);
    }
    return true;
}

static bool removeMode(Client &client, Channel &targetChannel, std::string flag, Server &server) {
    if (flag[1] == 'i')
        targetChannel.setInviteOnly(false);
    else if (flag[1] == 't')
        targetChannel.setTopicIsForMod(false);
    else if (flag[1] == 'k') 
        targetChannel.setPassword("", false);
    else if (flag[1] == 'o') {
        std::string nickname = client.getKey();
        Client *targetClient = server.getClientNickname(nickname);
        if (targetClient != NULL) {
            if (targetChannel.isUserModerator(*targetClient))
                targetChannel.removeModerator(*targetClient);
        } else {
            client.setMessage(ERR_NOSUCHNICK(nickname));
            return false;
        }
    }
    else if (flag[1] == 'l')
        targetChannel.setUserLimit(0);
    return true;
}

void Mode::accessChannel(Client &client, std::string target) {
    Channel *targetChannel;
    targetChannel = _server.getChannel(target);
    std::string flag(client.getKey());
    if (flag.size() == 2) {
        if (flag[0] == '+') {
            if (addMode(client, *targetChannel, flag, _server))
                client.setMessage(RPL_CHANNELMODEIS(client.getNickname(), targetChannel->getName(), targetChannel->getModes()));
        } else if (flag[0] == '-') {
            if (removeMode(client, *targetChannel, flag, _server))
                client.setMessage(RPL_CHANNELMODEIS(client.getNickname(), targetChannel->getName(), targetChannel->getModes()));
        }
    } else
        client.setMessage(ERR_UNKNOWNMODE(flag));
}

void Mode::execute(Client &client) {
    std::string target(client.getKey());
    if (target[0] == '#') {
        Channel *targetChannel;
        targetChannel = _server.getChannel(target);
        if (!targetChannel) {
            client.setMessage(ERR_NOSUCHCHANNEL(target));
            return;
        }
        if (!targetChannel->isUserInChannel(client)){
            client.setMessage(ERR_NOTONCHANNEL(targetChannel->getName()));
            return;
        }
        if (targetChannel->isUserModerator(client))
            accessChannel(client, target);
        else
            client.setMessage(ERR_CHANOPRIVSNEEDED(targetChannel->getName()));
    }
    else
        client.setMessage(ERR_NOSUCHCHANNEL(target));
}