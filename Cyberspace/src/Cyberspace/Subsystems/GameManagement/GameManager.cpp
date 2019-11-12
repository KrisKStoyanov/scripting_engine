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

	}

	Entity* Cyberspace::GameManager::GetInspectedEntity()
	{
		return m_InspectEntity;
	}

	void Cyberspace::GameManager::InspectEntity(Entity* _Entity)
	{
		m_InspectEntity = _Entity;
	}
}
