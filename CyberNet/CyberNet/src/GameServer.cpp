#include "GameServer.h"

GameServer::GameServer()
{
}

GameServer::~GameServer()
{
}

GameServer* GameServer::Create()
{
	return new GameServer();
}

int GameServer::Init()
{
	//Init ENet:
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occured while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);
	CreateServer();
}

void GameServer::CreateServer()
{
	m_Address.host = ENET_HOST_ANY;
	m_Address.port = 1234;
	m_Server = enet_host_create(&m_Address, 2, 2, 0, 0);
	if (m_Server == NULL) {
		fprintf(stderr, "An error occured while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
	printf("Server is running..\n");
	OnUpdate();
}

void GameServer::SendPacket(Cyberspace::PacketData* _data)
{
	ENetPacket* packet = enet_packet_create(_data, sizeof(_data), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
	//for (auto it : m_PeerMap) {
	//	enet_peer_send(it.second, 0, packet);
	//}
	for (ENetPeer* peer : m_Peers) {
		enet_peer_send(peer, 0, packet);
	}
}

void GameServer::OnUpdate()
{
	while (m_Running) {
		ENetEvent netEvent;
		while (enet_host_service(m_Server, &netEvent, 1000) > 0) {
			switch (netEvent.type) {
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n",
					netEvent.peer->address.host,
					netEvent.peer->address.port);
				netEvent.peer->data = &playerId;
				m_Peers.push_back(netEvent.peer);
				//Cyberspace::PacketData* peerData = new Cyberspace::PacketData(entityPositions);
				//SendPacket(peerData);
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received from %s on channel %u.\n",
					netEvent.packet->dataLength,
					netEvent.packet->data,
					&netEvent.peer->data,
					netEvent.channelID);
				enet_host_broadcast(m_Server, 0, netEvent.packet);
				enet_packet_destroy(netEvent.packet);

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", &netEvent.peer->data);
				netEvent.peer->data = NULL;
				//Check if peer is still connected and force disconnect
			}
		}
	}
	Terminate();
}

void GameServer::Terminate()
{
	enet_host_destroy(m_Server);
}
