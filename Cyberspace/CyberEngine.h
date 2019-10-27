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
	void Configure();
	void Update();
	void ProcessInput();
	void Deactivate();

	LocalState Engine_State = INACTIVE;

	GameInstance* Game = NULL;

	CyberRenderer* Engine_Renderer = NULL;
	CyberInterface* Engine_Interface = NULL;
	CyberPhysics* Engine_Physics = NULL;
	CyberAudio* Engine_Audio = NULL;
	CyberNet* Engine_Net = NULL;
};

