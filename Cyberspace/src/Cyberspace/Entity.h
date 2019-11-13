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
#include "./Subsystems/AssetManagement/Shader.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

#include "./Subsystems/Physics/PhysicsComponent.h"
#include "./Subsystems/Graphics/Mesh.h"
#include "./Subsystems/AssetManagement/Model.h"
#include "./Subsystems/Audio/AudioComponent.h"

#include "Core.h"
#include "Transform.h"

namespace Cyberspace {

	class CSPACE_API Entity
	{
	public:
		Entity();
		~Entity();

		void Clear();

		inline void SetTransform(Transform* _transform) { m_Transform = _transform; }
		inline Transform* GetTransform() { return m_Transform; }

		inline void SetModel(Model* _model) { m_Model = _model; }
		inline Model* GetModel() { return m_Model; }

		PhysicsComponent* m_PSX = NULL;
		AudioComponent* m_Audio = NULL;
	private:
		Transform* m_Transform;
		Model* m_Model = NULL;
	};
}


