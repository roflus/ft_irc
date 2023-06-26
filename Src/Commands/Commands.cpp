#include "../Src/Commands/Commands.hpp"

Commands::Commands(/* args */)
{
}

Commands::~Commands()
{
}


void  Commands::checkCommands(int currentSocket, char *buffer) {
    
    // Deze functie moet compleet anders, Het was puur om even te kijken
    // Of ik het in een loop kon doen,
    // ook al heeft de Harl mij wel geinspireerd
    const char *message;
    std::string receivedMessage(buffer);
    std::string test;
    int len = 0;
    std::string	operatorCommands[] = {
		"KICK",
		"INVITE", 
		"TOPIC",
		"MODE"
	};

    for (int i = 0; i < 4; i++)
    {
        len = operatorCommands[i].length();
        test = receivedMessage.substr(0, len);
        if (test == operatorCommands[i]) {
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