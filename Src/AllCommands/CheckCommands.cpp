#include "../../include/CheckCommands.hpp"

CheckCommands::CheckCommands(Server &server) : _server(server) {
    this->_commands["INVITE"] = new Invite(this->_server);
    this->_commands["JOIN"] = new Join(this->_server);
    this->_commands["KICK"] = new Kick(this->_server);
    this->_commands["MODE"] = new Mode(this->_server);
    this->_commands["NICK"] = new Nick(this->_server);
    this->_commands["PASS"] = new Pass(this->_server);
    this->_commands["PRIVMSG"] = new Privmsg(this->_server);
    this->_commands["QUIT"] = new Quit(this->_server);
    this->_commands["TOPIC"] = new Topic(this->_server);
    this->_commands["USER"] = new User(this->_server);
}

CheckCommands::~CheckCommands() {
    for (std::map<std::string, Commands *>::iterator it = _commands.begin(); it != _commands.end(); ++it)
        delete it->second;
}

Commands*   CheckCommands::getCommand(std::string &command) const {
    return this->_commands.at(command);
}

void  CheckCommands::enterServer(Client &client) {
    //Should make check for Pass | NICK Heeft nog een argument nodig
    std::string key = client.getKey();
    if (key == "PASS" || key == "USER"){
        executeCommand(client, key);
    }
    if (client.getNickname() != "" && client.getPassword() != "" && client.getUsername() != "") {
        if (client.getPassword() == _server.getPassword())
            client.setRegistrated(true);
        else {
            client.setErrorMessage("Wrong password.\n");
        }
    }
    else if (key == "QUIT")
        executeCommand(client, key);
    else {
        std::string message = "CHOOSE PASS, USER OR QUIT\n";
        send(client.getSocket(), message.c_str(), message.size(), 0);
    }
}

void  CheckCommands::findCommand(Client &client) {
    if (client.getRegistrated() == false) {
        enterServer(client);
    }
    else {
        std::string key = client.getKey();
        std::map<std::string, Commands*>::iterator iter = _commands.find(key);
        if (iter != _commands.end())
            executeCommand(client, key);
        else 
            client.setErrorMessage("Start with a valid Command\n");
    }
} 

void  CheckCommands::executeCommand(Client &client, std::string key) {
    Commands*    command;
    command = this->getCommand(key);
    command->execute(client);
}
