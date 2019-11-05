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
#include "./Subsystems/Graphics/Renderer.h"
#include "./Subsystems/Interface/UISystem.h"
#include "./Subsystems/Networking/CyberNet.h"
#include "./Subsystems/Audio/AudioSystem.h"
#include "./Subsystems/Physics/PhysicsSystem.h"
#include "Subsystems/Window/EngineWindow.h"

#include "CyberEvent.h"

#include "GameInstance.h"
#include "EventList.h"

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

	EngineWindow* E_Window = NULL;
	Renderer* E_Renderer = NULL;
	PhysicsSystem* E_Physics = NULL;
	AudioSystem* E_Audio = NULL;
	UISystem* E_UI = NULL;
	CyberNet* E_Net = NULL;

	std::vector<Entity*> EntityCollection;
	std::queue<CyberEvent*> EventQueue;

private:
	float DeltaTime = 0.0f, LastFrameTime = 0.0f;
};

