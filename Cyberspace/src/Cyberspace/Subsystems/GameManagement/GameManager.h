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

	struct GMProps {
		std::string PlayerTag;
		std::string VehicleTag;
		std::string EnvironmentTag;
		std::string StartMapTag;
		glm::vec3 PlayerSpawnPosition;
		float PlayerSpeed;
		GMProps(
			std::string _playerTag = "Vehicle",
			std::string _vehicleTag = "VehicleModel",
			std::string _environmentTag = "Canyon",
			std::string _startMapTag = "TitleScreen",
			glm::vec3 _playerSpawnPosition = glm::vec3(0.0f, 0.0f, -10.0f),
			float _playerSpeed = 5.0f) :
			PlayerTag(_playerTag),
			VehicleTag(_vehicleTag),
			EnvironmentTag(_environmentTag),
			StartMapTag(_startMapTag),
			PlayerSpawnPosition(_playerSpawnPosition),
			PlayerSpeed(_playerSpeed)
		{}
	};


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


