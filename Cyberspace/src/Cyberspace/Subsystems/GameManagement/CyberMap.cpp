#include "cspacepch.h"
#include "CyberMap.h"

namespace Cyberspace {
	CyberMap::CyberMap(std::unordered_map<int, Entity*> _mapEntities) {
		m_Entities = _mapEntities;
	}

	CyberMap::~CyberMap() {

	}
	void CyberMap::AddEntity(int _id, Entity* _entity)
	{
		m_Entities[_id] = _entity;
	}
	void CyberMap::RemoveEntity(int _id)
	{
		m_Entities.erase(_id);
	}
}