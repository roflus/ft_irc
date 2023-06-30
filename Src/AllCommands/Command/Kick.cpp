#include "../../../include/Commands.hpp"

Kick::Kick(Server& server) : Commands(server)
{
}

Kick::~Kick()
{
}

void  Kick::execute(Client &client)
{
    //Voorbeeld van printen
    // Direct(it = client.getArguments().begin()) of extra var
    // nog altijd een space teveel

    const char* message;

    // eigen functie in client?
    std::string stringMessage;
    std::deque<std::string> deque = client.getArguments();
    std::deque<std::string>::const_iterator it;
    for (it = deque.begin(); it != deque.end(); ++it) {
        stringMessage += *it;
        stringMessage += " ";
    }
    stringMessage += "\n";
    message = stringMessage.c_str();
    send(client.getSocket(), message, strlen(message), 0);
} 