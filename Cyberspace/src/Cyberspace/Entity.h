#pragma once
#include "Core.h"
#include "./Subsystems/Graphics/Vertex.h"
#include "./Subsystems/AssetManagement/Shader.h"

#include "./Subsystems/Physics/PhysicsComponent.h"
#include "./Subsystems/Graphics/Mesh.h"
#include "./Subsystems/AssetManagement/Model.h"
#include "./Subsystems/Audio/AudioComponent.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

#include "Transform.h"

namespace Cyberspace {

	class CSPACE_API Entity
	{
	public:
		Entity();
		Entity(const Entity& _other);
		~Entity();

		void Clear();

		inline void SetTransform(Transform* _transform) { m_Transform = _transform; }
		inline Transform*& GetTransform() { return m_Transform; }

		inline void SetModel(Model* _model) { m_Model = _model; }
		inline Model*& GetModel() { return m_Model; }

		PhysicsComponent* m_PSX = NULL;
		AudioComponent* m_Audio = NULL;
	private:
		Transform* m_Transform;
		Model* m_Model = NULL;
	};
}


