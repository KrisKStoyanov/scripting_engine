#pragma once
#include <unordered_map>
#include "../../Entity.h"

namespace Cyberspace {

	class CSPACE_API CyberMap {
	public:
		CyberMap();
		~CyberMap();
		void AddEntity(std::string _tag, Entity* _entity);
		void RemoveEntity(std::string _tag);
		std::unordered_map<std::string, Entity*> MapEntities;
	};
}