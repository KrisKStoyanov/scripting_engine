#pragma once
#include "../../Entity.h"

namespace Cyberspace {

	class CSPACE_API CyberMap {
	public:
		CyberMap(std::unordered_map<int, Entity*> _mapEntities);
		CyberMap();
		~CyberMap();
		void AddEntity(int _id, Entity* _entity);
		void RemoveEntity(int _id);
		std::unordered_map<int, Entity*> m_Entities;
		glm::vec3 m_SpawnPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	};
}