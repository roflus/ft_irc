#include "../../include/Server.hpp"

Server::Server(const std::string &port, const std::string &password) : 
    _serverSocket(-1),
    _port(atoi(port.c_str())), 
    _password(password),
    _checkCommands(new CheckCommands(*this))
    {}
    /* Bind listen dus server opstarten kan hier?
    Maaaar..... dan moeten we dus namespace doen, kan wel ? wat denk jij? is wel BigBrain 
    voor nu is het nog hetzelfde als eerst */

Server::~Server() {
    stopServer();
}

Client *Server::GetClient(int fd) {
    std::map<int, Client*>::iterator it = _clients.find(fd);
    if (it != _clients.end())
        return it->second;
    else
        throw ServerException("Client not found");
}

void Server::stopServer() {
    if (_serverSocket != -1) {
        close(_serverSocket);
        _serverSocket = -1;
    }

    // Close all client sockets
    for (int i = 0; i <= MAX_CLIENTS; ++i) {
        if (_pollfds[i].fd != -1) {
            close(_pollfds[i].fd);
            _pollfds[i].fd = -1;
        }
    }
}

void Server::startServer() {
    struct sockaddr_in serverAddress, clientAddress;

    /* Create serversocket en throw exception en dan in de main opvangen met try en chatch want */
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1)
        throw ServerException("Failed to create server socket");

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(_port);

    // Bind server socket to the specified address and port
    if (bind(_serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
        throw ServerException("Failed to bind server socket");

    // Listen for incoming connections
    if (listen(_serverSocket, 1) == -1)
        throw ServerException("Failed to listen server socket");

    std::cout << "Server started with port number: " << _port << ". Waiting for connections..." << std::endl;

    // Add server socket to the pollfd vector
    pollfd serverPollfd;
    serverPollfd.fd = _serverSocket;
    serverPollfd.events = POLLIN;
    _pollfds.push_back(serverPollfd);
    // FUNCTION FOR RUNNING SERVER
    runServer();
    return;
}

void Server::runServer(){
    Client *client;
    while (true) {
        // Use poll to wait for activity on any of the connected sockets
        if (poll(_pollfds.data(), _pollfds.size(), -1) == -1)
            throw ServerException("Failed to listen server socket");

        if (_pollfds[0].revents & POLLIN) {
            std::cout << "kom je heir" << std::endl;
            acceptClient();
        }

        for (int i = 1; i <= _clients.size(); ++i){
            if ((_pollfds[i].revents & POLLIN)) {
                // pollfd &_pollfd = _pollfds[i];
                client = GetClient(_pollfds[i].fd);
                if (!HandleData(*client))
                    throw ServerException("FOUT");
                /* 
                    - maak pollfd aan zet pollfd[i] erin
                    - maak clien aan en zet server.getclient(intfd) erin.
                    - Server funcite handledata(client en fd?)?
                    - daarin client.handlebuffer()
                    - daarin gaan parsen? iig het in de buffer van de client zetten.
                    - daarna kunnen we met pollin kijken ofzo ik weet het niet bladsflasdf????..?
                */
                receiveMessages(*client);
                _checkCommands->findCommand(*client);
            }
        }
    }
    stopServer();
    return ;
}

void Server::receiveMessages(Client &client){
    // Check for activity on the client sockets (incoming data)

    std::map<int, Client*>::iterator it = _clients.find(client.getSocket());
    if (it != _clients.end())
    {
        std::cout << "Received message from " << it->second->getSocket() << it->second->getBuffer() << std::endl;
        // command.checkCommands(currentSocket, buffer);
    }
}


void Server::acceptClient(){
    /* hier een nieuwe Client class aanmaken de socket naar accept zetten en dan in die map zetten */
    Client *client;
    client = new Client;
    socklen_t clientAddressSize = sizeof(client->getSockaddr());
    client->setSocket(accept(_serverSocket, (sockaddr *)client->getSockaddr(), &clientAddressSize));
    if (client->getSocket() == -1)
        throw ServerException("Failed to listen server socket");

    pollfd clientPollfd;
    clientPollfd.fd = client->getSocket();
    clientPollfd.events = POLLIN;
    _pollfds.push_back(clientPollfd);
    
    _clients[client->getSocket()] = client;
    std::string message = "Hello, welcome to Rolf and Quilfort's Server! What is your Nickname?\n";
    send(client->getSocket(), message.c_str(), message.size(), 0);
}

bool Server::HandleData(Client &client) {

    // ?? bool functie weet ik nog niet zeker?
    if (client.HandleBuffer())
        return true;
    return false;
    // client.Handlebuffer
    // in handle buffer recv()
    // dan checken en dan overzetten in de string buffer van client
    // dan kunnen we in recievemessage voor nu uitprinten vanuit de client
}


// void Server::disconnectClient(int index){
//     int currentSocket = _pollfds[index].fd;
//     // Client has closed the connection or an error occurred
//     std::cout << "Client disconnected. Client socket descriptor: " << currentSocket << std::endl;
//     close(currentSocket);
//     // _pollfds[index].fd = -1; // Mark as unused
//     // Find the client in the vector
//     std::map<int, std::string>::iterator it;
//     for (it = clientSockets.begin(); it != clientSockets.end(); ++it) {
//         if (it->first == currentSocket) {
//             break;

//         }
//     }
//     if (it != clientSockets.end()) {
//         clientSockets.erase(it);
//     }
//     std::cout << "connectedClients: " << connectedClients << std::endl;

//     if (connectedClients == 0) {
//         stopServer();
//         // Iets anders voor vinden, maar ik had geen zin meer in dit
//         exit (0);
//     }
// }

