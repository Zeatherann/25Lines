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

    virtual void Render()const{}
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

class Level{
public:
    Tilemap Ground;
    Tilemap Walls;
    Tilemap Special;
    set<Entity*> Objects;
    //lua_State* MyState;
    Level(const string& LevelName):Ground(),Walls(),Special(),Objects()/*,myState(NULL)*/{
        //MyState=luaL_newstate();
        /// Load Level from file. LevelName_ground.png LevelName_walls.png LevelName_special.png LevelName_objects.yml LevelName_script.lua
    }
    ~Level(){
        for(Entity* Iter:Objects){
            delete Iter;
        }
        //luaL_closestate(MyState);
    }
    void Render(int X,int Y,int Rows,int Columns)const{
        Ground.Render(X,Y,Rows,Columns);
        Walls.Render(X,Y,Rows,Columns);
        for(Entity* Iter:Objects){
            sf::FloatRect Viewf(X,Y,X+Rows,Y+Columns);
            if(Viewf.contains(Iter->Loc.first,Iter->Loc.second))Iter->Render();
        }
        Special.Render(X,Y,Rows,Columns);
    }
    void Update(){
        /// Call script.update
        for(Entity* Iter:Objects){
            Iter->Update();
        }
    }
};

class LevelBoss:public Level{};
class LevelTower:public Level{};
class LevelRealm:public Level{};
class LevelWorld:public Level{};

int main() {
    Entity* e = new Item(Item::FOOD);
    e->Update();
    shared_ptr<sf::Thread> MyThread;
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
            clients.push_back(client);
            MyThread=shared_ptr<sf::Thread>(new sf::Thread(&ClientConnection::Run,client));
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
    if(MyThread)MyThread->launch();
    Window.create({800,640},"25 Lines",sf::Style::Close);
    sf::Event Events;
    while(Window.isOpen()){
        Window.clear({64,64,64});
        while(Window.pollEvent(Events)){
            switch(Events.type){
                case sf::Event::Closed:{
                    Window.close();
                    break;
                }default:;
            }
        }// END EVENTS

        /// Add Updating/Drawing/Ect
        Window.display();
    }
    return 0;
}

sf::RenderWindow Window;
