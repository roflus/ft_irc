#ifndef REPLIES_HPP
#define REPLIES_HPP

#define MSG_WELCOME(user)   "001 " + user + " Welcome to our irc server"
#define MSG_INVITING(user, target, channel) ":" + user + " INVITE " + target + " " + channel
#define MSG_JOIN(user, channel)  ":" + user + " JOIN :" + channel
#define MSG_KICK(user, target, channel, reason) ":" + user + " KICK " + channel + " " + target + " :" + reason
#define MSG_NICK(user, nickname) ":" + user + " NICK " + nickname
#define MSG_PRIVMSG(user, target, message) ":" + user + " PRIVMSG " + target + " :" + message

#define RPL_TOPIC(user, channel, topic) "332 " + user + " " + channel + " :" + topic
#define RPL_CHANNELMODEIS(user, channel, modes) "324 " + user + " " + channel + " " + modes
#define RPL_INVITING(user, target, channel) "341 " + user + " " + target + " " + channel

#endif