#pragma once
#include <vector>
#include "Cyberspace/Entity.h"
#include "Cyberspace/Subsystems/Networking/CyberNet.h"

#include <cstdio>
#include <string>

#include <enet/enet.h>
#include <iostream>

//Not part of the DLL (using API namespace for object references)
class GameServer
{
public:
	std::unordered_map<int, glm::vec3> entityPositions;
	static GameServer* Create();
	int Init();
	void CreateServer();
	void SendPacket(Cyberspace::PacketData* _data);
	void BroadcastPacket(Cyberspace::PacketData* _data);
	void ProcessPacket(ENetPacket* _packet);
	void OnUpdate();
	void Terminate();
	ENetAddress m_Address;
	ENetHost* m_Server;
	bool m_Running = true;
	std::vector<ENetPeer*> m_Peers;
	std::string playerId = "1";
private:
	GameServer();
	~GameServer();
};

