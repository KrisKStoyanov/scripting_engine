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

#include <enet/enet.h>
#include "../../CyberEvent.h"
#include "../../Core.h"

namespace Cyberspace {

	struct NetworkProps {
		NetworkProps() {};
	};

	class CSPACE_API CyberNet
	{
	public:
		static CyberNet* Create(const NetworkProps& _props = NetworkProps());
		CyberNet(const NetworkProps& _props);
		~CyberNet();
		void Init(const NetworkProps& _props);
		void CreateServer();
		void CreateClient();
		bool UpdateServer();
		void SendPacketToPeer();
		void DisconectPeer();
		void HandleEvent(CyberEvent* _Event);
		void ConnectToHost();
		void Terminate();
		ENetAddress CR_Address;
		ENetHost* CR_Server;
		ENetHost* CR_Client;
		ENetPeer* CR_Peer;
	};
}


