/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

// ----------------------------------------------------------------------
// RakNet version 1.0
// Filename ChatExample.cpp
// Very basic chat engine example
// ----------------------------------------------------------------------

#include "MessageIdentifiers.h"

#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"
#include "BitStream.h"
#include "PacketLogger.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "RakNetTypes.h"
#ifdef _WIN32
#include "Kbhit.h"
#include "WindowsIncludes.h" // Sleep
#else
#include "Kbhit.h"
#include <unistd.h> // usleep
#endif
#include "Gets.h"
#include "include/Client.hpp"
#include "include/entities/Arena.hpp"
#include "include/managers/InputManager.hpp"
#include <string>
#include <iostream> 

#if LIBCAT_SECURITY==1
#include "SecureHandshake.h" // Include header for secure handshake
#endif

unsigned char GetPacketIdentifier(RakNet::Packet *p);

Client* Client::m_instance = 0;

Client* Client::instance(){
    if (!m_instance)
        m_instance = new Client();

    return m_instance;
}

//Constructor
Client::Client(){}

void Client::send(char const *mens){
		std::cout<<"Sending-> "<<mens<<std::endl;
		client->Send(mens, (int) strlen(mens)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::recive(){
	m_action = 0;
	#ifdef _WIN32
		Sleep(30);
	#else
		usleep(30 * 1000);
	#endif
	char const * t_first = "";

	for (p=client->Receive(); p; client->DeallocatePacket(p), p=client->Receive())
	{
		packetIdentifier = GetPacketIdentifier(p);
		switch (packetIdentifier)
		{

		case ID_CONNECTION_LOST:
			printf("ID_CONNECTION_LOST\n");
			break;

		case ID_CONNECTION_REQUEST_ACCEPTED:
			// This tells the client they have connected
			printf("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
			printf("My external address is %s\n", client->GetExternalID(p->systemAddress).ToString(true));
			t_first = "player";
			send(t_first);
			break;
		default:
			//printf("-\n");
			// It's a client, so just show the message
			std::string t_messageReceived;
			t_messageReceived.append(reinterpret_cast<const char*>(p->data));
			readMessage(t_messageReceived);
			printf("Receiving-> %s\n",p->data);
			break;
		}
	}
}

void Client::start()
{
	client=RakNet::RakPeerInterface::GetInstance();

	// Record the first client that connects to us so we can pass it to the ping function
	RakNet::SystemAddress clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
	// Get our input
	puts("Enter the client port to listen on");
	Gets(clientPort,sizeof(clientPort));
	if (clientPort[0]==0)
		strcpy(clientPort, "0");

	puts("Enter IP to connect to");
	Gets(ip, sizeof(ip));
	client->AllowConnectionResponseIPMigration(false);
	if (ip[0]==0)
		strcpy(ip, "127.0.0.1");
	
		
	puts("Enter the port to connect to");
	Gets(serverPort,sizeof(serverPort));
	if (serverPort[0]==0)
		strcpy(serverPort, "1234");

	RakNet::SocketDescriptor socketDescriptor(atoi(clientPort),0);
	socketDescriptor.socketFamily=AF_INET;
	client->Startup(8,&socketDescriptor, 1);
	client->SetOccasionalPing(true);


	#if LIBCAT_SECURITY==1
	char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
	FILE *fp = fopen("publicKey.dat","rb");
	fread(public_key,sizeof(public_key),1,fp);
	fclose(fp);
	#endif

	#if LIBCAT_SECURITY==1
	RakNet::PublicKey pk;
	pk.remoteServerPublicKey=public_key;
	pk.publicKeyMode=RakNet::PKM_USE_KNOWN_PUBLIC_KEY;
	bool b = client->Connect(ip, atoi(serverPort), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"), &pk)==RakNet::CONNECTION_ATTEMPT_STARTED;	
	#else
	RakNet::ConnectionAttemptResult car = client->Connect(ip, atoi(serverPort), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"));
	RakAssert(car==RakNet::CONNECTION_ATTEMPT_STARTED);
	#endif

	printf("\nMy IP addresses:\n");
	unsigned int i;
	for (i=0; i < client->GetNumberOfAddresses(); i++)
	{
		printf("%i. %s\n", i+1, client->GetLocalIP(i));
	}

	printf("My GUID is %s\n", client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
	puts("'quit' to quit. 'stat' to show stats. 'ping' to ping.\n'disconnect' to disconnect. 'connect' to reconnnect. Type to talk.");

	// Loop for input

		// This sleep keeps RakNet responsive

	// Be nice and let the server know we quit.
	//client->Shutdown(300);

	// We're done with the network
	//RakNet::RakPeerInterface::DestroyInstance(client);
}

int Client::getActions(int p_player){
	return m_action;
}

unsigned char GetPacketIdentifier(RakNet::Packet *p)
{
	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}

void Client::readMessage(std::string p_message){
	std::string t_delimiter = ":";
	std::string t_property = p_message.substr(0, p_message.find(t_delimiter)); // t_property is "scott"
	if(t_property == "new"){
		
		std::string t_player = p_message.substr(p_message.find(t_delimiter)+1, p_message.length());
		m_yourPlayer = atoi(t_player.c_str());
		m_yourPlayerString = t_player;
		for(int i = -1; i < m_yourPlayer; ++i){
			Arena::getInstance()->addPlayer();
		}
		InputManager::instance()->setOnlineControl(m_yourPlayer);
	}
	else{
		std::string t_action = p_message.substr(p_message.find(t_delimiter)+1, p_message.length());	
		int mns = atoi(t_action.c_str());
		m_action = mns;
	}
}

int Client::getPlayer(){
	return m_yourPlayer;
}

void Client::sendAction(int p_action){
	if(p_action == 0) // 0 es el valor vacio de raknet
		p_action = 1;
    std::string t_toSend = m_yourPlayerString + ":" + std::to_string(p_action);
    char const *t_toSendChar = t_toSend.c_str();
	send(t_toSendChar);
}

