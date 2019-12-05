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
	ENetPacket* packet = enet_packet_create(_data, sizeof(_data), ENET_PACKET_FLAG_RELIABLE);
	//for (auto it : m_PeerMap) {
	//	enet_peer_send(it.second, 0, packet);
	//}
	for (ENetPeer* peer : m_Peers) {
		enet_peer_send(peer, 0, packet);
	}
}

void GameServer::BroadcastPacket(Cyberspace::PacketData* _data)
{
	ENetPacket* packet = enet_packet_create(_data, sizeof(int) + 3 * sizeof(float), ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(m_Server, 0, packet);
}

void GameServer::ProcessPacket(ENetPacket* _packet)
{
	Cyberspace::PacketData* data = (Cyberspace::PacketData*)_packet->data;
	printf("Received Packet:\n"
		"Length: %u \n"
		"Contents: EntityID: %u Entity Position: X:%f, Y:%f, Z:%f \n",
		_packet->dataLength,
		data->entityID,
		data->entityXPos, data->entityYPos, data->entityZPos);
	entityPositions[data->entityID] = glm::vec3(data->entityXPos, data->entityYPos, data->entityZPos);
	BroadcastPacket(data);
}

void GameServer::OnUpdate()
{
	while (m_Running) {
		ENetEvent netEvent;
		while (enet_host_service(m_Server, &netEvent, 500) > 0) {
			switch (netEvent.type) {
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n",
					netEvent.peer->address.host,
					netEvent.peer->address.port);
				netEvent.peer->data = (void*)&playerId;
				m_Peers.push_back(netEvent.peer);
				//Cyberspace::PacketData* peerData = new Cyberspace::PacketData(entityPositions);
				//SendPacket(peerData);
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				ProcessPacket(netEvent.packet);
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
