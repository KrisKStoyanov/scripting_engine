#pragma once
#include <iostream>
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

#include "Entity.h"
#include "Shader.h"
#include "CyberRenderer.h"
#include "CyberInterface.h"
#include "CyberPhysics.h"
#include "CyberAudio.h"
#include "CyberNet.h"

#include "GameInstance.h"

enum LocalState {
	STARTING,
	ACTIVE,
	INACTIVE
};

class CyberEngine
{
public:
	CyberEngine();
	~CyberEngine();

	bool Init(const char* _WindowTitle, int _WindowWidth = 800, int _WindowHeight = 600);
	void Start();
	void Configure();
	void Update();
	void ProcessInput();
	void Deactivate();

	LocalState CR_CurrentState = INACTIVE;

	static void GLFW_Error_Callback(int _Error, const char* _Description);

	unsigned int CR_WindowWidth = 800;
	unsigned int CR_WindowHeight = 600;
	GLFWwindow* CR_MainWindow = NULL;

	GameInstance* Game = NULL;

	CyberRenderer* CR_Renderer = NULL;
	CyberInterface* CR_Interface = NULL;
	CyberPhysics* CR_Physics = NULL;
	CyberAudio* CR_Audio = NULL;
	CyberNet* CR_Net = NULL;
};

