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
		std::vector<glm::vec3> m_Positions;
		std::string PacketName = "LUL";
		PacketData(std::vector<glm::vec3> _positions) : m_Positions(_positions) {}
	};

	class CSPACE_API CyberNet
	{
	public:
		static CyberNet* Create(const NetworkProps& _props = NetworkProps());
		~CyberNet();
		void Init(const NetworkProps& _props);
		void CreateClient();
		void ConnectToHost();
		void SendPacket(PacketData* _data);
		void Disconnect();
		void OnUpdate(std::queue<CyberEvent*>& _EventQueue, std::vector<glm::vec3> _UpdatedPositions);
		void Terminate();
		ENetHost* m_Client;
		ENetPeer* m_Peer;
	private:
		CyberNet(const NetworkProps& _props);
	};
}


