/// **********************************************************
///	Class:			Networking
///	Programmers:	Joseph Deschene-Poole 
/// Date:			December 2011
/// **********************************************************

#include "Networking.h"

#define HOSTPORT 59999
#define CLIENTPORT 60000

// Constructor / Destructor

Networking::Networking()
{
	peer = RakNet::RakPeerInterface::GetInstance();
	isServer = false;
}

Networking::~Networking()
{
	RakNet::RakPeerInterface::DestroyInstance(peer);
}


// Start Host, Allows the starting of the server
void Networking::startHost()
{
	RakNet::SocketDescriptor sd( HOSTPORT, 0 );
	peer->Startup( 2, &sd, 1 );
	peer->SetMaximumIncomingConnections( 2 );
	printf("Host started \n");
	isServer = true;
}

// Allows the starting of the client
// Peer IP is the IP of the server
void Networking::startClient( const char* peerIP )
{
	// Startup
	RakNet::SocketDescriptor sd( CLIENTPORT, 0 );
	peer->Startup( 2, &sd, 1 );
	// Connection Code
	printf("starting connection \n");
	peer->Connect( peerIP, HOSTPORT, 0, 0 )!=RakNet::CONNECTION_ATTEMPT_STARTED;
	printf("connected \n");
}


// Send Data - sets up the bitstream for data sedning
void Networking::sendData( unsigned char message )
{
	RakNet::MessageID typeID;
	//RakNet::AddressOrGUID addressTemp;

	typeID = ID_CHAT_MESSAGE;
	//addressTemp.SetUndefined();

	RakNet::BitStream *bs = new RakNet::BitStream();
	bs->Write( typeID );
	bs->Write( message );
	RakNet::AddressOrGUID address;
	address.SetUndefined();

	if(!isServer)
	{
		printf("Sending Data To Server...\n");
		peer->Send( bs, IMMEDIATE_PRIORITY, UNRELIABLE_SEQUENCED, 0, 
			    address, true, 0 );
	}
	else
	{
		RakNet::SystemAddress sa = peer->GetSystemAddressFromGuid(peer->GetMyGUID());
		RakNet::SystemAddress Systems[10];
		for (int i = 0; i < 10; i++)
		{
			Systems[i] = sa;
		}
		unsigned short numberOfSystems = 10;
		this->getConnectionList(Systems, &numberOfSystems);
		
		for (int i = 0; i < numberOfSystems; i++)
		{
			address.systemAddress = Systems[i];
			
			if (address.systemAddress != sa)
			{ 

				printf("Sending Data to Client " + i);
				printf("\n");
				peer->Send(bs,IMMEDIATE_PRIORITY, UNRELIABLE_SEQUENCED, 0, 
					address, true, 0 );
			}
		}

	}
}

// if data recived returns true
// else false
bool Networking::isReceive()
{
	RakNet::MessageID typeID;
	RakNet::Packet *packet = 0;
	unsigned char message;

	for ( packet = peer->Receive(); packet; peer->DeallocatePacket( packet ), packet=peer->Receive() )
	{
		return true;	
	}

	return false;
}

// Checks for and deals with recieved data
unsigned char Networking::receiveData()
{
	RakNet::MessageID typeID;
	RakNet::Packet *packet = 0;
	unsigned char message = 0;
	// if data recieved
	for ( packet = peer->Receive(); packet; peer->DeallocatePacket( packet ), packet=peer->Receive() )
	{
		printf("Recieving Data...\n");
		// if packet is not empty
		switch ( packet->data[0] )
		{
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			printf( "Another client has disconnected.\n" );
			break;
		case ID_REMOTE_CONNECTION_LOST:
			printf( "Another client has lost the connection.\n" );
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			printf( "Another client has connected.\n" );
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			printf( "Our connection request has been accepted.\n" );
			break;					
		case ID_NEW_INCOMING_CONNECTION:
			printf( "A connection is incoming.\n" );
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			printf( "The server is full.\n" );
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			if ( isServer )
			{
				printf( "A client has disconnected.\n" );
			} 
			else 
			{
				printf( "We have been disconnected.\n" );
			}
			break;
		case ID_CONNECTION_LOST:
			if ( isServer )
			{
				printf( "A client lost the connection.\n" );
			} 
			else 
			{
				printf( "Connection lost.\n" );
			}
			break;
		case ID_CHAT_MESSAGE: // If chat found
			{
				// Handles Packet and returns char buffer
				message = packetHandler( packet );

				//printf( ( const char* )message );

				peer->DeallocatePacket( packet );
				// if server sends it back out
				if ( isServer )
					sendData( message );
			}
			break;
		case ID_PING: // if ping
			{
				printf("Recieved Ping");
				sendPing(); // sends ping back out
			}
		default:
			printf( "Message with identifier %i has arrived.\n", packet->data[0] );
			break;
		}
	}
	return message;
}

// Shuts down peer
void Networking::shutDown()
{
	peer->Shutdown( 1000 );
}

// Handles recieved Packets
unsigned char Networking::packetHandler( RakNet::Packet *packet )
{
	unsigned char message;
	RakNet::BitStream receivedStream( packet->data, packet->length, false );
	receivedStream.IgnoreBytes( sizeof( RakNet::MessageID ) );
	receivedStream.Read( message );
	return message;
}

// gets a list of the connections
void Networking::getConnectionList(RakNet::SystemAddress *Systems, unsigned short *NofS)
{
	peer->GetConnectionList(Systems, NofS);
}

// Disconnects
void Networking::Disconnect(void)
{
	peer->CloseConnection(peer->GetSystemAddressFromIndex(0),true,0);
	isConnected=false;
}

// Returns if it is a server
bool Networking::getIsServer()
{
	return this->isServer;
}

// Sends a Ping
void Networking::sendPing()
{
	if ( nextSendTime >= TBP)
	{
		RakNet::MessageID typeID;

		typeID = ID_PING;

		// sets up bit stream for sending ping
		RakNet::BitStream *bs = new RakNet::BitStream();
		bs->Write( typeID );
		bs->Write( "" );
		RakNet::AddressOrGUID address = peer->GetSystemAddressFromIndex(0);

		// if not server
		if(!isServer)
		{
			printf("Sending Ping To Server...\n");
			peer->Send( bs, IMMEDIATE_PRIORITY, UNRELIABLE_SEQUENCED, 0, 
					address, true, 0 );
		}
		else // sends ping to everyone
		{
			RakNet::SystemAddress sa = peer->GetSystemAddressFromGuid(peer->GetMyGUID());
			RakNet::SystemAddress Systems[10];
			for (int i = 0; i < 10; i++)
			{
				Systems[i] = sa;
			}
			unsigned short numberOfSystems = 10;
			this->getConnectionList(Systems, &numberOfSystems);
		
			for (int i = 0; i < numberOfSystems; i++)
			{
				address.systemAddress = Systems[i];
		
				if (address.systemAddress != sa)
				{ 

					printf("Sending Ping to Client %i");
					printf("\n");
					peer->Send(bs,IMMEDIATE_PRIORITY, UNRELIABLE_SEQUENCED, 0, 
						address, true, 0 );
				}
			}

		}
		nextSendTime = 0;
	}
	else
		nextSendTime++;
}
