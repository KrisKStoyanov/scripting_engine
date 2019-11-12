#pragma once
#include <vector>
#include "Cyberspace/Entity.h"
#include "Cyberspace/Subsystems/Networking/CyberNet.h"

#include <cstdio>
#include <string>

#include <enet/enet.h>
#include <iostream>

class GameServer
{
public:
	//std::vector<Entity*> ServerEntityCollection;
	static GameServer* Create();
	int Init();
	void CreateServer();
	void SendPacket(Cyberspace::PacketData* _data);
	void OnUpdate();
	void Terminate();
	ENetAddress m_Address;
	ENetHost* m_Server;
	bool m_Running = true;
	std::vector<ENetPeer*> m_Peers;
private:
	GameServer();
	~GameServer();
};

