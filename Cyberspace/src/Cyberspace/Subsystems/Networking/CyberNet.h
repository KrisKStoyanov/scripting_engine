#pragma once
#include "../../Core.h"

#include <enet/enet.h>
#include "../../CyberEvent.h"
#include "../../Core.h"
#include "../../Entity.h"
#include "../../../EngineProps.h"
#include <queue>

namespace Cyberspace {
		
	struct PacketData {
		int entityID;
		glm::vec3 entityPos;
		PacketData(int _id, glm::vec3 _pos) : entityID(_id), entityPos(_pos) {}
	};

	class CSPACE_API CyberNet
	{
	public:
		static CyberNet* Create(const NetworkProps& _props = NetworkProps());
		~CyberNet();
		void Init(const NetworkProps& _props);
		void CreateClient();
		bool ConnectToHost();
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


