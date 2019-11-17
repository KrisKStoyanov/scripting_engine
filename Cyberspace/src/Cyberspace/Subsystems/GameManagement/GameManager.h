#pragma once
#include <unordered_map>
#include <string>
#include "../../Entity.h"
#include "../../Core.h"
#include "CyberMap.h"
#include <queue>
#include "../../CyberEvent.h"
#include "../AssetManagement/Model.h"
#include "../../../EngineProps.h"

namespace Cyberspace {

	class CSPACE_API GameManager
	{
	public:
		static GameManager* Create(
			std::unordered_map<std::string, Model*> _models, 
			const GMProps& _props = GMProps());
		~GameManager();
		void Init(std::unordered_map<std::string, Model*> _models, const GMProps& _props);
		void OnUpdate(std::queue<CyberEvent*>& _EventQueue, float _DeltaTime);
		void Terminate();

		float PlayerSpeed = 5.0f;

		int PlayerEntityID;
		int CurrentMapID;
		std::unordered_map<int, CyberMap*> GameMaps;
	private:
		GameManager(std::unordered_map<std::string, Model*> _models,
			const GMProps& _props = GMProps());
	};
}


