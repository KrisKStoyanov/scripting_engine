#pragma once
#include "./Subsystems/Graphics/Vertex.h"
#include "./Subsystems/AssetManagement/Shader.h"

#include "./Subsystems/Graphics/Mesh.h"
#include "./Subsystems/AssetManagement/Model.h"

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
	private:
		Transform* m_Transform;
		Model* m_Model = NULL;
	};
}


