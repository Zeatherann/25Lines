#include "main.hpp"

HOST_OR_JOIN HostOrJoin() {
    cout << "(h)ost or (j)oin: ";
    char option;
    cin >> option;
    if (option == 'h') {
        return HOST;
    } else if (option == 'j') {
        return JOIN;
    } else {
        cout << "Invalid input.\n";
        return HostOrJoin();
    }
}

class ClientConnection {
public:
    sf::SocketTCP Connection;

    ClientConnection(sf::SocketTCP Connection) : Connection(Connection) {}

    void Run() {
        cout << "Running a ClientConnection.\n";
        while (true) {
        }
    }
};

int main()
{
    HOST_OR_JOIN choice = HostOrJoin();
    if (choice == HOST) {
        vector<ClientConnection*> clients;

        sf::SocketTCP listener;
        if (!listener.Listen(PORT)) {
            cout << "Error: Unable to listen on port " << PORT << ".\n";
            exit(UNABLE_TO_LISTEN);
        }

        while (true) {
            sf::IPAddress ClientAddress;
            sf::SocketTCP Socket;
            if (listener.Accept(Socket, &ClientAddress) != sf::Socket::Done) {
                cout << "Error: Something went wrong while trying to accept a client connection!\n";
            }
            ClientConnection* client = new ClientConnection(Socket);
            std::function<void()> run = std::bind(&ClientConnection::Run, client);
            clients.push_back(client);
            /* I would love to find a close replacement for std::thread (perhaps boost::thread?).
                Though I don't know what special things you have to do to include boost::thread.
                I am having odd compiler errors right now; these errors are killing the runtime executable when using libraries, would probably have to clean/reinstall compiler or something.

                Also: Added the basics for my Tilemap class, this will draw nearly all of the geometry of any level in the game. I have added 23 semicolons.
                Your semicolon counter is busted (lol) and only counts 12 of my added semicolons.
            */
            /*std::thread thread(run)*/;
        }
    } else if (choice == JOIN) {
        cout << "Joining! (Please implement.)\n";
    }
    return 0;
}
