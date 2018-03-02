#ifndef CLIENT
#define CLIENT


#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include <iostream>

class Client{
    public:
        static Client& instance();
        Client();
        ~Client();
        void start();
        void recive();
        void send(char const *mens);
        int getActions(int p_player);
        void readMessage(std::string p_message);
        int getPlayer();
        void sendAction(int p_action);
    private:
        RakNet::RakNetStatistics *rss;
        RakNet::RakPeerInterface *client;
	    RakNet::Packet* p;
        unsigned char packetIdentifier;
        char message[2048];
        RakNet::SocketDescriptor socketDescriptor;
        char ip[64], serverPort[30], clientPort[30];
        int m_action;
        int m_yourPlayer;
        std::string m_yourPlayerString;
};

#endif