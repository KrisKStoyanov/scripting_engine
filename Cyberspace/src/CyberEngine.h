#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <enet/enet.h>

#include "Entity.h"
#include "./Subsystems/Graphics/CyberRenderer.h"
#include "./Subsystems/Interface/CyberInterface.h"
#include "./Subsystems/Networking/CyberNet.h"
#include "./Subsystems/Audio/CyberAudio.h"
#include "./Subsystems/Physics/CyberPhysics.h"
#include "Subsystems/Window/CyberWindow.h"

#include "CyberEvent.h"

#include "GameInstance.h"
#include "EventList.h"

#include "objloader.h"
 

enum class LocalState {
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
	float ComputeDeltaTime(float _CurrentFrame);
	void Update();
	void Terminate();

	LocalState Engine_State = LocalState::INACTIVE;

	GameInstance* Game = NULL;

	CyberRenderer* Engine_Renderer = NULL;
	CyberInterface* Engine_Interface = NULL;
	CyberPhysics* Engine_Physics = NULL;
	CyberAudio* Engine_Audio = NULL;
	CyberNet* Engine_Net = NULL;
	CyberWindow* Engine_Window = NULL;

	std::vector<Entity*> EntityCollection;
	std::queue<CyberEvent*> EventQueue;

private:
	float DeltaTime = 0.0f, LastFrameTime = 0.0f;
};

