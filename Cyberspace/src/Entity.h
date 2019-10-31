#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vertex.h"
#include "./Subsystems/Renderer/Shader.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

#include "./Subsystems/Physics/PhysicsComponent.h"
#include "./Subsystems/Renderer/GraphicsComponent.h"
#include "./Subsystems/Audio/AudioComponent.h"

class Entity
{
public:
	Entity(glm::vec3 _Position, glm::vec3 _Direction);
	~Entity();

	glm::vec3 Position;
	glm::vec3 Direction;

	void Setup(GraphicsComponent* _GFX = NULL, PhysicsComponent* _PSX = NULL, AudioComponent* _Audio = NULL);
	void Clear();

	GraphicsComponent* GFX_Comp = NULL;
	PhysicsComponent* PSX_Comp = NULL;
	AudioComponent* Audio_Comp = NULL;
};

