#include "../../../include/Commands.hpp"

Mode::Mode(Server &server) : Commands(server) {}

Mode::~Mode() {}

static void addMode(Client &client, Channel &targetChannel, std::string flag, Server &server) {
    if (flag[1] == 'i')
        targetChannel.setInviteOnly(true);
    else if (flag[1] == 't')
        targetChannel.setTopicIsForMod(true);
    else if (flag[1] == 'k') {
        std::string password = client.getKey();
        if (!password.empty())
            targetChannel.setPassword(password);
        else
            client.setMessage(ERR_PASSWDMISMATCH(client.getNickname()));
    }
    else if (flag[1] == 'o') {
        std::string nickname = client.getKey();
        Client *targetClient = server.getClientNickname(nickname);
        if (targetClient != NULL) {
            if (!targetChannel.isUserModerator(*targetClient))
                targetChannel.addModerator(*targetClient);
        }
        else
            client.setMessage(ERR_NOSUCHNICK(nickname));
    }
    else if (flag[1] == 'l') {
        std::string limitString = client.getKey();
        for (char c : limitString) {
            if (!std::isdigit(c)) {
                client.setMessage(":" + client.getNickname() +  " :Argument for userlimit must be a number.");
                return ;
            }
        }
        int limit = atoi(limitString.c_str());
        targetChannel.setUserLimit(limit);
    }
}

static void removeMode(Client &client, Channel &targetChannel, std::string flag, Server &server) {
    if (flag[1] == 'i')
        targetChannel.setInviteOnly(false);
    else if (flag[1] == 't')
        targetChannel.setTopicIsForMod(false);
    else if (flag[1] == 'k') 
        targetChannel.setPassword("");
    else if (flag[1] == 'o') {
        std::string nickname = client.getKey();
        Client *targetClient = server.getClientNickname(nickname);
        if (targetClient != NULL) {
            if (targetChannel.isUserModerator(*targetClient)) {
                targetChannel.removeModerator(*targetClient);
        } else
            client.setMessage(ERR_NOSUCHNICK(nickname));
    }
    else if (flag[1] == 'l')
        targetChannel.setUserLimit(0);
    }
}

void Mode::accessChannel(Client &client, std::string target) {
    Channel *targetChannel;
    targetChannel = _server.getChannel(target);
    std::string flag(client.getKey());
    if (flag.size() == 2) {
        if (flag[0] == '+') {
            addMode(client, *targetChannel, flag, _server);
        } else if (flag[0] == '-') {
            removeMode(client, *targetChannel, flag, _server);
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
            client.setMessage(ERR_NOSUCHCHANNEL(targetChannel->getName()));
            return;
        }
        else if (targetChannel->isUserModerator(client))
            accessChannel(client, target);
        else
            client.setMessage(ERR_CHANOPRIVSNEEDED(targetChannel->getName()));
    }
    else
        client.setMessage(ERR_NOSUCHCHANNEL(target));
}