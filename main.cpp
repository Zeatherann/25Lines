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
    sf::TcpSocket* Connection;

    ClientConnection(sf::TcpSocket* Connection) : Connection(Connection) {}

    void Run() {
        cout << "Running a ClientConnection.\n";
        while (true) {
            
        }
    }
};

class Entity {
public:
    static set<Entity*> Entities;
    static _3de::ResourceCache<sf::Texture> Textures;
    enum Types {ITEM};
    const Entity::Types Type;
    pairf Loc;
    sf::Texture& Texture;
    
    Entity(Entity::Types type, pairf loc, string texture) : Type(type), Loc(loc), Texture(Textures.New(texture)) {
        Entities.insert(this);
    }
    
    virtual ~Entity() {
        Entities.erase(this);
    }
    
    virtual void Update()=0;
    
    virtual void Render() {}
};

set<Entity*> Entity::Entities;
_3de::ResourceCache<sf::Texture> Entity::Textures;

class Item : public Entity {
public:
    enum Types {FOOD, GOLD, KEY};
    const Item::Types Type;
    
    Item(Item::Types type, pairf loc={0,0}, string texture="default.png") : Entity(ITEM, loc, texture), Type(type) {
        
    }
    
    virtual void Update() {
        cout << "I'm an Item, bro!\n";
    }
};

int main() {
    Entity* e = new Item(Item::FOOD);
    e->Update();
    HOST_OR_JOIN choice = HostOrJoin();
    if (choice == HOST) {
        vector<ClientConnection*> clients;

        sf::TcpListener listener;
        if (listener.listen(PORT) != sf::Socket::Done) {
            cout << "Error: Unable to listen on port " << PORT << ".\n";
            exit(UNABLE_TO_LISTEN);
        }

        while (true) {
            sf::TcpSocket* Socket = new sf::TcpSocket();
            if (listener.accept(*Socket) != sf::Socket::Done) {
                cout << "Error: Something went wrong while trying to accept a client connection!\n";
            }
            ClientConnection* client = new ClientConnection(Socket);
            std::function<void()> run = std::bind(&ClientConnection::Run, client);
            clients.push_back(client);
            boost::thread thread(run);
            thread.detach();
        }
    } else if (choice == JOIN) {
        cout << "Joining!\n";
        sf::TcpSocket Socket;
        sf::Socket::Status status = Socket.connect("127.0.0.1", PORT);
        if (status != sf::Socket::Done)
        {
            cout << "Error: Unable to connect to server on port " << PORT << ". Is it running?\n";
            exit(UNABLE_TO_CONNECT);
        }
    }
    return 0;
}
