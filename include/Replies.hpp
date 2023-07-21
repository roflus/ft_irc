#ifndef REPLIES_HPP
#define REPLIES_HPP

#define MSG_WELCOME(user)   "001 " + user + " Welcome to our irc server"
#define MSG_INVITING(user, target, channel) ":" + user + " INVITED " + target + " to channel :" + channel
#define MSG_JOIN(user, channel)  ":" + user + " JOIN :" + channel
#define MSG_KICK(user, target, channel, reason) ":" + user + " KICKED :" + target + "from :" + channel + " " + reason
#define MSG_MODE(user, channel, modes) ":" + user + " " + channel + " " + modes
#define MSG_NICK(user, nickname) ":" + user + " Set nickname to :" + nickname
#define MSG_USER(username) ":" + username + " :username is set" 
#define MSG_PRIVMSG(user, target, message) ":" + user + " PRIVMSG " + target + " :" + message

#define RPL_TOPIC(channel, topic) "332 " + channel + " :" + topic
#define RPL_CHANNELMODEIS(user, channel, modes) "324 " + channel + modes
#define RPL_INVITING(channel , target) "341 " + channel + target  // returned by server to indicat that the attempted invite message was successful.
#endif