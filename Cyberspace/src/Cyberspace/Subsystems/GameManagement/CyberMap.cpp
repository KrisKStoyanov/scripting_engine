#include "CyberMap.h"

namespace Cyberspace {
	CyberMap::CyberMap() {

	}

	CyberMap::~CyberMap() {

	}
	void CyberMap::AddEntity(std::string _tag, Entity* _entity)
	{
		MapEntities[_tag] = _entity;
	}
	void CyberMap::RemoveEntity(std::string _tag)
	{
		MapEntities.erase(_tag);
	}
}