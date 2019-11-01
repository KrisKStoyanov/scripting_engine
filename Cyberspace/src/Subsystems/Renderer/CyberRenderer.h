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
#include "Shader.h"

#include "../../Entity.h"
#include "../../CyberEvent.h"
#include "../../EventList.h"
#include "Camera.h"
#include <queue>

class CyberRenderer
{
public:
	CyberRenderer(bool& _InitStatus, int _WindowWidth, int _WindowHeight);
	~CyberRenderer();
	bool Init(int _WindowWidth, int _WindowHeight);
	void Draw(GLuint _VAO, GLuint _ElementCount);
	void Update(std::queue<CyberEvent*>& _EventQueue, std::vector<Entity*> _EntityCollection);
	void Terminate();

	void(*MoveForward)(EventType) = MoveForwardEvent;
	void(*MoveBackward)(EventType) = MoveBackwardEvent;
	void(*MoveLeft)(EventType) = MoveLeftEvent;
	void(*MoveRight)(EventType) = MoveRightEvent;

	Entity* TestEntity = NULL;
	Camera* MainCamera = NULL;
};

