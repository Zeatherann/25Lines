#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <thread>

using namespace std;

const int PORT = 4567;

enum HOST_OR_JOIN { HOST, JOIN };
enum EXIT_CODES { UNABLE_TO_LISTEN=1 };

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
            std::thread thread(run);
        }
    } else if (choice == JOIN) {
        cout << "Joining! (Please implement.)\n";
    }
    return 0;
}
