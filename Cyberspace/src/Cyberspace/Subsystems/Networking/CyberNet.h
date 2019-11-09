#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <queue>

#include <enet/enet.h>
#include "../../CyberEvent.h"
#include "../../Core.h"
#include "../../Entity.h"

namespace Cyberspace {

	struct NetworkProps {
		NetworkProps() {};
	};
		
	struct PacketData {
		std::vector<glm::vec3> m_Positions;
		PacketData(std::vector<glm::vec3> _positions) : m_Positions(_positions) {}
	};

	class CSPACE_API CyberNet
	{
	public:
		static CyberNet* Create(const NetworkProps& _props = NetworkProps());
		CyberNet(const NetworkProps& _props);
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
	};
}


