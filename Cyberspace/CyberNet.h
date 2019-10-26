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

class CyberNet
{
public:
	CyberNet();
	~CyberNet();
	bool Activate();
	void CreateServer();
	void CreateClient();
	bool UpdateServer();
	void SendPacketToPeer();
	void DisconectPeer();
	void ConnectToHost();
	void Deactivate();	
	ENetAddress CR_Address;
	ENetHost* CR_Server;
	ENetHost* CR_Client;
	ENetPeer* CR_Peer;
};

