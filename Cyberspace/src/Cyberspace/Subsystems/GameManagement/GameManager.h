#pragma once
#include <unordered_map>
#include <string>
#include "../../Entity.h"
#include "../../Core.h"
#include "CyberMap.h"
#include <queue>
#include "../../CyberEvent.h"
#include "../AssetManagement/Model.h"
#include "../AssetManagement/AssetManager.h"

namespace Cyberspace {

	class CSPACE_API GameManager
	{
	public:
		static GameManager* Create(const GMProps& _props = GMProps());
		GameManager(const GMProps& _props);
		~GameManager();
		void Init(const GMProps& _props);
		void OnUpdate(std::queue<CyberEvent*> _EventQueue);
		void Terminate();

		Entity* PlayerEntity = NULL;
		Model* PlayerModel = NULL;
		float PlayerSpeed;

		std::string CurrentMap = "Test";
		std::unordered_map<std::string, CyberMap*> GameMaps;
	};
}


