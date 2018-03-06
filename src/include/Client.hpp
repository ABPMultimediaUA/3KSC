#ifndef CLIENT
#define CLIENT

class InputManager;
class Arena;

#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include <iostream>
#include <vector>

class Client{
    public:
        static Client& instance();
        Client();
        ~Client();
        void start();
        void update();
        void listen();
        void send(char const *mens);
        int getActions(int p_player);
        void readMessage(std::string p_message);
        int getPlayer();
        void sendAction(int p_action);
        const std::vector<std::string> explode(const std::string& s, const char& c);
        void spawnItem(int p_type, int x, int y);
        
    private:
        InputManager*   m_inputManager;
        Arena*          m_arena;

        RakNet::RakNetStatistics *rss;
        RakNet::RakPeerInterface *client;
	    RakNet::Packet* p;
        unsigned char packetIdentifier;
        char message[2048];
        RakNet::SocketDescriptor socketDescriptor;
        char ip[64], serverPort[30], clientPort[30];
        int m_action;
        int m_yourPlayer;
        bool m_debug = false;
        std::string m_yourPlayerString;
        
};

#endif