#include "GameManager.h"

namespace Cyberspace {
	GameManager* GameManager::Create()
	{
		return new GameManager();
	}
	GameManager::~GameManager()
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
