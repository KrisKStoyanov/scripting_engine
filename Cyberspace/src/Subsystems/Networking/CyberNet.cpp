#include "CyberNet.h"

CyberNet::CyberNet(bool& _InitStatus)
{
	_InitStatus = Init();
}

CyberNet::~CyberNet()
{
}

bool CyberNet::Init()
{
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return false;
	}
	return true;
}

void CyberNet::CreateServer()
{
	CR_Address.host = ENET_HOST_ANY;
	CR_Address.port = 1234;

	CR_Server = enet_host_create(&CR_Address, 32, 2, 0, 0);

	if (CR_Server == NULL) {
		fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
}

void CyberNet::CreateClient()
{
	CR_Client = enet_host_create(NULL, 1, 2, 0, 0);
	if (CR_Client == NULL) {
		fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
		exit(EXIT_FAILURE);
	}
}

bool CyberNet::UpdateServer()
{
	ENetEvent NetEvent;
	while (enet_host_service(CR_Client, &NetEvent, 1000) > 0) {
		switch (NetEvent.type) {
		case ENET_EVENT_TYPE_CONNECT:
			printf("A new client connected from %x:%u.\n",
				NetEvent.peer->address.host,
				NetEvent.peer->address.port);

			//NetEvent.peer->data = "Client information";

			break;
		case ENET_EVENT_TYPE_RECEIVE:
			printf("A packet of length %u containing %s was received from %s on channel %u.\n",
				NetEvent.packet->dataLength,
				NetEvent.packet->data,
				NetEvent.peer->data,
				NetEvent.channelID);

			enet_packet_destroy(NetEvent.packet);

			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%s disconnected.\n", (char*)NetEvent.peer->data);

			NetEvent.peer->data = NULL;
		}
	}
	return false;
}

void CyberNet::SendPacketToPeer()
{
	ENetPacket* Packet = enet_packet_create("packet", strlen("packet") + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_packet_resize(Packet, strlen("packetfoo") + 1);
	strcpy((char*)Packet->data[strlen("packet")], "foo");
	//strcpy(&Packet->data[strlen("packet")], "foo");

	enet_peer_send(CR_Peer, 0, Packet);
	enet_host_flush(CR_Server);
}

void CyberNet::DisconectPeer()
{
	ENetEvent NetEvent;

	enet_peer_disconnect(CR_Peer, 0);
	while (enet_host_service(CR_Client, &NetEvent, 3000) > 0) {
		switch (NetEvent.type) {
		case ENET_EVENT_TYPE_RECEIVE:
			enet_packet_destroy(NetEvent.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			puts("Disconnection succeeded");
			return;
			break;
		}
	}
	enet_peer_reset(CR_Peer);
}

void CyberNet::HandleEvent(CyberEvent* _Event)
{

}

void CyberNet::ConnectToHost()
{
	ENetEvent NetEvent;
	enet_address_set_host(&CR_Address, "localhost");
	CR_Address.port = 1234;

	CR_Peer = enet_host_connect(CR_Client, &CR_Address, 2, 0);
	if (CR_Peer == NULL) {
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}

	if (enet_host_service(CR_Client, &NetEvent, 5000) > 0 &&
		NetEvent.type == ENET_EVENT_TYPE_CONNECT) {
		puts("Connection is successful");
	}
	else {
		enet_peer_reset(CR_Peer);
		puts("Connection failed");
	}
}

void CyberNet::Terminate()
{
	if (CR_Peer != NULL) {
		DisconectPeer();
	}

	if (CR_Client != NULL) {
		enet_host_destroy(CR_Client);
	}
	if (CR_Server != NULL) {
		enet_host_destroy(CR_Server);
	}
	
	atexit(enet_deinitialize);
}

