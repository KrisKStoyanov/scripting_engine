#pragma once
#include "../../Entity.h"
#include "../../Core.h"

namespace Cyberspace {
	class CSPACE_API GameManager
	{
	public:
		static GameManager* Create();
		~GameManager();
		Entity* GetInspectedEntity();
		void InspectEntity(Entity* _Entity);
	private:
		Entity* m_InspectEntity = nullptr;
	};
}


