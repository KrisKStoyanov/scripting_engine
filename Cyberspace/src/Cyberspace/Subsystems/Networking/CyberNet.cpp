#include "cspacepch.h"
#include "CyberNet.h"

namespace Cyberspace {
	CyberNet* Cyberspace::CyberNet::Create(const NetworkProps& _props)
	{
		return new CyberNet(_props);
	}

	CyberNet::CyberNet(const NetworkProps& _props)
	{
		Init(_props);
	}

	CyberNet::~CyberNet()
	{
		Terminate();
	}

	void CyberNet::Init(const NetworkProps& _props)
	{
		if (enet_initialize() != 0) {
			fprintf(stderr, "An error occurred while initializing ENet.\n");
		}
		atexit(enet_deinitialize);
		CreateClient();
	}


	void CyberNet::CreateClient()
	{
		m_Client = enet_host_create(NULL, 1, 2, 0, 0);
		if (m_Client == NULL) {
			fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
			exit(EXIT_FAILURE);
		}
	}

	bool CyberNet::ConnectToHost() {
		ENetAddress address;
		enet_address_set_host(&address, ENET_HOST_ANY);
		address.port = 1234;
		m_Peer = enet_host_connect(m_Client, &address, 2, 0);
		if (m_Peer == NULL) {
			fprintf(stderr, "No available peers for initiating an ENet connection\n");
			exit(EXIT_FAILURE);
		}
		ENetEvent netEvent;
		if (enet_host_service(m_Client, &netEvent, 5000) > 0 && netEvent.type == ENET_EVENT_TYPE_CONNECT) {
			puts("Connection to server succeeded.");
			return true;
		}
		else {
			enet_peer_reset(m_Peer);
			puts("Connection to server failed.");
			return false;
		}
	}

	void CyberNet::ProcessPacket(ENetPacket* _packet)
	{
		Cyberspace::PacketData* data = (Cyberspace::PacketData*)_packet->data;
		printf("Received Packet:\n"
			"Length: %u \n"
			"Contents: EntityID: %u Entity Position: X:%f, Y:%f, Z:%f \n",
			_packet->dataLength,
			data->entityID,
			data->entityPos.x, data->entityPos.y, data->entityPos.z);
	}

	void CyberNet::SendPacket(PacketData* _data)
	{
		ENetPacket* packet = enet_packet_create(_data, sizeof(_data), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
		enet_peer_send(m_Peer, 0, packet);
	}

	void CyberNet::Disconnect()
	{
		enet_peer_disconnect(m_Peer, 0);
		ENetEvent netEvent;
		while (enet_host_service(m_Client, &netEvent, 1000) > 0) {
			switch (netEvent.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(netEvent.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				std::vector<glm::vec3> TESTLUL;
				TESTLUL.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
				m_Peer->data = (void*)"LUL";
				puts("Disconnection succeeded.");
				return;
			}
		}
	}

	void CyberNet::OnUpdate(std::queue<CyberEvent*>& _EventQueue)
	{
		ENetEvent netEvent;
		while (enet_host_service(m_Client, &netEvent, 0) > 0) {
			switch (netEvent.type) {
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n",
					netEvent.peer->address.host,
					netEvent.peer->address.port);
				netEvent.peer->data = &netEvent.data;
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				//printf("A packet of length %u containing %s was received  from %s on channel %u.\n",
				//	netEvent.packet->dataLength,
				//	netEvent.packet->data,
				//	netEvent.peer->data,
				//	netEvent.channelID);
				ProcessPacket(netEvent.packet);
				enet_packet_destroy(netEvent.packet);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", static_cast<const char*>(netEvent.peer->data));
				netEvent.peer->data = NULL;
			}
		}
	}

	void CyberNet::Terminate()
	{
		Disconnect();
		if (m_Client != NULL) {
			enet_host_destroy(m_Client);
		}
	}
}


