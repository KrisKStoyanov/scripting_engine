#include "GameManager.h"

namespace Cyberspace {
	GameManager* GameManager::Create(const GMProps& _props)
	{
		return new GameManager(_props);
	}

	GameManager::GameManager(const GMProps& _props) {
		Init(_props);
	}

	GameManager::~GameManager()
	{

	}

	void GameManager::Init(const GMProps& _props)
	{
		CurrentMap = _props.StartMapTag;
		GameMaps[CurrentMap] = new CyberMap();

		PlayerEntity = new Entity();
		PlayerEntity->SetTransform(new Transform(_props.PlayerSpawnPosition));
		GameMaps[CurrentMap]->MapEntities[_props.PlayerTag] = PlayerEntity;
		GameMaps[CurrentMap]->PlayerSpawnPosition = _props.PlayerSpawnPosition;

		PlayerSpeed = _props.PlayerSpeed;
	}
	void GameManager::OnUpdate(std::queue<CyberEvent*> _EventQueue)
	{
	}
	void GameManager::Terminate()
	{
	}
}
