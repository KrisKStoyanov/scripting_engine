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
		void CreateClient();
		void ConnectToHost();
		void Disconnect();
		void OnUpdate();
		void Terminate();
		ENetHost* m_Client;
		ENetPeer* m_Peer;
	};
}


