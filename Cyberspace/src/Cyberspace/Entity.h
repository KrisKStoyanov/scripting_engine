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
#include "./Subsystems/Graphics/Vertex.h"
#include "./Subsystems/Graphics/Shader.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

#include "./Subsystems/Physics/PhysicsComponent.h"
#include "./Subsystems/Graphics/Mesh.h"
#include "./Subsystems/Graphics/Model.h"
#include "./Subsystems/Audio/AudioComponent.h"

#include "Core.h"

namespace Cyberspace {
	class CSPACE_API Entity
	{
	public:
		Entity(glm::vec3 _Position, glm::vec3 _Direction);
		~Entity();

		glm::vec3 Position;
		glm::vec3 Direction;

		void Configure(Model* _Model = NULL, PhysicsComponent* _PSX = NULL, AudioComponent* _Audio = NULL);
		void Clear();

		Model* m_Model = NULL;
		PhysicsComponent* m_PSX = NULL;
		AudioComponent* m_Audio = NULL;
	};
}


