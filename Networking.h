/// **********************************************************
///	Class:			Networking
///	Programmers:	Joseph Deschene-Poole, Matthew Sadana 
/// Date:			December 2011
/// **********************************************************

#ifndef _Networking_MES_
#define _Networking_MES_

#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"

#define MAX_CLIENTS 1
#define SERVER_PORT 1234
#define CLIENT_PORT 4356

#define TBP 500 // Time Between Pings

enum messages
{
	ID_CHAT_MESSAGE = ID_USER_PACKET_ENUM,
	ID_PING	= ID_USER_PACKET_ENUM + 1
};

class Networking
{
public:
	Networking();
	virtual ~Networking();
	void startHost();
	void startClient( const char* peerIP );
	void sendData( unsigned char message );
	bool isReceive();
	unsigned char receiveData();
	void shutDown();
	unsigned char packetHandler( RakNet::Packet *packet );
	void getConnectionList(RakNet::SystemAddress *Systems, unsigned short *NofS);
	void Disconnect(void);
	bool getIsServer();
	void sendPing();

private:
	int nextSendTime;
	RakNet::RakPeerInterface *peer;
	bool isConnected;
	bool isServer;
};


#endif