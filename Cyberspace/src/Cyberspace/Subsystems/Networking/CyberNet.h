#pragma once

#include <enet/enet.h>
#include "../../CyberEvent.h"
#include "../../Entity.h"
#include "../../../EngineProps.h"
#include <queue>

namespace Cyberspace {
		
	struct PacketData {
		int entityID;
		float entityXPos;
		float entityYPos;
		float entityZPos;
		PacketData(int _id, float _xPos, float _yPos, float _zPos) : 
			entityID(_id), entityXPos(_xPos), entityYPos(_yPos), entityZPos(_zPos)  {}
	};

	class CSPACE_API CyberNet
	{
	public:
		static CyberNet* Create(const NetworkProps& _props = NetworkProps());
		~CyberNet();
		void Init(const NetworkProps& _props);
		void CreateClient();
		bool ConnectToHost();
		void ProcessPacket(ENetPacket* _packet);
		void SendPacket(PacketData* _data);
		void Disconnect();
		void OnUpdate(std::queue<CyberEvent*>& _EventQueue);
		void Terminate();
		ENetHost* m_Client;
		ENetPeer* m_Peer;
	private:
		CyberNet(const NetworkProps& _props);
	};
}


