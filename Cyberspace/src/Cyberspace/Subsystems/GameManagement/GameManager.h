#pragma once
#include <unordered_map>
#include <string>
#include "../../Entity.h"
#include "../../Core.h"
#include "CyberMap.h"

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
		CyberMap* MainMap = NULL;
	};
}


