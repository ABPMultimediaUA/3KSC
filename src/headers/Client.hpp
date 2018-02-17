#ifndef CLIENT
#define CLIENT


#include "RakPeerInterface.h"
#include "RakNetStatistics.h"

class Client{
    public:
        static Client* instance();
        Client();
        ~Client();
        void start();
        void recive();
        void send(char const *mens);
        int getActions(int p_player);
    private:
        static Client* m_instance;
        RakNet::RakNetStatistics *rss;
        RakNet::RakPeerInterface *client;
	    RakNet::Packet* p;
        unsigned char packetIdentifier;
        bool isServer = false;
        char message[2048];
        RakNet::SocketDescriptor socketDescriptor;
        char ip[64], serverPort[30], clientPort[30];
        int m_action;
};

#endif