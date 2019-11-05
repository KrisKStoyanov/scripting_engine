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

#include "Entity.h"
#include "./Subsystems/Graphics/Renderer.h"
#include "./Subsystems/Interface/UISystem.h"
#include "./Subsystems/Networking/CyberNet.h"
#include "./Subsystems/Audio/AudioSystem.h"
#include "./Subsystems/Physics/PhysicsSystem.h"

class GameInstance
{
public:
	GameInstance();
	~GameInstance();
	
	void Start();
	void Configure();
	void AddEntity(std::string _EntityName, std::vector<Vertex> _EntityVerts, std::vector<GLuint> _EntityIndices);
	void Update();
	void Clear();
	void Exit();

	bool Active = false;
	GLFWwindow* GameWindow = NULL;
	std::vector<Entity*> EntityCollection;
	//std::map<std::string, Entity*> EntityCollection;
};

