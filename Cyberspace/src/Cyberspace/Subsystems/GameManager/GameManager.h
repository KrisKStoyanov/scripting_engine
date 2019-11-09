#pragma once
#include "../../Entity.h"
#include "../../Core.h"

namespace Cyberspace {

	struct GMProps {
		GMProps () {}
	};

	class CSPACE_API GameManager
	{
	public:
		static GameManager* Create(const GMProps& _props = GMProps());
		GameManager(const GMProps& _props);
		~GameManager();
		void Init(const GMProps& _props);
		Entity* GetInspectedEntity();
		void InspectEntity(Entity* _Entity);
	private:
		Entity* m_InspectEntity = nullptr;
	};
}


