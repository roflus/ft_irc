#ifndef ERRORS_HPP
#define ERRORS_HPP

/* Errors that will be returned that have something to do with nickname*/
#define ERR_NOSUCHNICK(nickname) "401 " + nickname + " :No such nickname"
#define ERR_NONICKNAMEGIVEN(nickname) "431 " + nickname + " :No nickname given"
#define ERR_NICKNAMEINUSE(nickname) "433 " + nickname + " :Nickname/username is already in use"
#define ERR_ERRONEUSNICKNAME(nickname) "432 " + nickname + " :Erroneus nickname"

/* Errors that will be returned that have something to do with channel*/
#define ERR_NOSUCHCHANNEL(channelname) "403 " + channelname + " :No such channel"
#define ERR_USERNOTINCHANNEL(nickname, channel) "441 " + nickname + " " + channel + " :They aren't on that channel"
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel"
#define ERR_USERONCHANNEL(user, channel) "443 " + user + channel + " :is already on channel"

/* Errors that will be returned that have something to do with register */
#define ERR_NOTREGISTERED(user) "451 " + user + " :You have not registered"
#define ERR_ALREADYREGISTRED(user) "462 " + user + " :You may not reregister"
#define ERR_PASSWDMISMATCH(user) "464 " + user + " :Password incorrect"

/* Erorrs that will be returned that have something to do with commands */
#define ERR_UNKNOWNCOMMAND(user, key) "421 " + user + " " + key + " :Unknown command "
#define ERR_NEEDMOREPARAMS(key) "461 " + key + " :Not enough parameters"

/* Erorrs that will be returned that have something to do with command JOIN*/
#define ERR_CHANNELISFULL(channel) "471 " + channel + " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN(channel) "473 " + channel + " :Cannot join/invite channel (+i)"
#define ERR_BADCHANNELKEY(channel) "475 " + channel + " :Cannot join channel (+k)"

/* Erorrs that will be returned that have something to do with command MODE*/
#define ERR_UNKNOWNMODE(mode) "472 " + mode + " :is unknown mode char to me"

/* Erorrs that will be returned that have something to do with commands with operator privileges*/
#define ERR_CHANOPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator"

/*  deze mischien weet ik niet?  */
#define ERR_UMODEUNKNOWNFLAG(user) "501 " + user + " :Unknown MODE flag"
#define ERR_NORECIPIENT(command) "411 " + ":No recipient given " + command
#define ERR_NOTEXTTOSEND(target) "412 " + target + ":No text to send"

#endif 