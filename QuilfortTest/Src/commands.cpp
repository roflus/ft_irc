#include "../include/server.hpp"

void Server::sendWelcomeMessage() {
    const char* message = "Hello, welcome to Rolf and Quilfort's Server! What is your Nickname?\n";
    send(clientSocket, message, strlen(message), 0);
}

void  Server::checkCommands(int currentSocket, char *buffer) {
    
    // Deze functie moet compleet anders, Het was puur om even te kijken
    // Of ik het in een loop kon doen,
    // ook al heeft de Harl mij wel geinspireerd
    
    std::string receivedMessage(buffer);
    std::string test;
    int len = 0;
    std::string	commandArray[] = {
		"KICK",
		"INVITE", 
		"TOPIC",
		"MODE"
	};
    
    for (int i = 0; i < 4; i++)
    {
        len = commandArray[i].length();
        test = receivedMessage.substr(0, len);
        if (test == commandArray[i]) {
            message = "THIS IS A FUTURE COMMAND\n";
            send(currentSocket, message, strlen(message), 0);
        }
    }
    // BREAK bij juiste Index. Daarna Een Switch
    //switch (i) {
	//	case 0:
    //		FUNCTIE VOOR KICK
  	//	case 1:
    //		FUNCTIE VOOR INVITE
 	//	case 2:
    //		FUNCTIE VOOR TOPIC
  	//	case 3:
    //		FUNCTIE VOOR MODE
	//		break ;
	//	default:
    //		DOEN NIKS
}