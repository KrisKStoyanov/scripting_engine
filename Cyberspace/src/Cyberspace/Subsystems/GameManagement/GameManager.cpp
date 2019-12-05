#include "cspacepch.h"
#include "GameManager.h"

namespace Cyberspace {
	GameManager* GameManager::Create(std::unordered_map<std::string, Model*> _models, const GMProps& _props)
	{
		return new GameManager(_models, _props);
	}

	GameManager::GameManager(std::unordered_map<std::string, Model*> _models, const GMProps& _props) {
		Init(_models, _props);
	}

	GameManager::~GameManager()
	{

	}

	void GameManager::Init(std::unordered_map<std::string, Model*> _models, const GMProps& _props)
	{
		PlayerEntityID = _props.m_PlayerID;
		int EnvironmentID = PlayerEntityID++;
		CurrentMapID = _props.m_MapID;
		GameMaps[CurrentMapID] = new CyberMap();
		GameMaps[CurrentMapID]->m_SpawnPosition = _props.m_SpawnPosition;
		GameMaps[CurrentMapID]->AddEntity(PlayerEntityID, new Entity());
		GameMaps[CurrentMapID]->AddEntity(EnvironmentID, new Entity());
		GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->SetTransform(new Transform(_props.m_SpawnPosition));
		GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->SetModel(_models[_props.m_PlayerModelTag]);
		GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->Rotate(-90.0f, 0.0f, -90.0f);
		GameMaps[CurrentMapID]->m_Entities[EnvironmentID]->SetTransform(new Transform(_props.m_SpawnPosition));
		GameMaps[CurrentMapID]->m_Entities[EnvironmentID]->SetModel(_models[_props.m_EnvironmentModelTag]);
		GameMaps[CurrentMapID]->m_Entities[EnvironmentID]->GetTransform()->Rotate(-90.0f, 0.0f, -90.0f);
	}
	void GameManager::OnUpdate(std::queue<CyberEvent*>& _EventQueue, EngineProps _props, float _DeltaTime)
	{
		if (_props.m_NetProps.m_ClientState == ClientState::Connected) {
			for (auto it : _props.m_NetProps.m_NetEntityPositions) {
				GameMaps[CurrentMapID]->m_Entities[it.first]->GetTransform()->SetPosition(it.second);
			}
		}
		if (!_EventQueue.empty()) {
			switch (_EventQueue.front()->Type) {
			case EventType::VEHICLE_MOVE_FORWARD:
				GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->Translate(
					GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->GetPosition()
					+ glm::vec3(0.0f, 0.0f, -1.0f) * PlayerSpeed * _DeltaTime);
				_EventQueue.pop();
				break;

			case EventType::VEHICLE_MOVE_BACKWARD:
				GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->Translate(
					GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->GetPosition()
					+ glm::vec3(0.0f, 0.0f, 1.0f) * PlayerSpeed * _DeltaTime);
				_EventQueue.pop();
				break;

			case EventType::VEHICLE_MOVE_LEFT:
				GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->Translate(
					GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->GetPosition()
					+ glm::vec3(-1.0f, 0.0f, 0.0f) * PlayerSpeed * _DeltaTime);
				_EventQueue.pop();
				break;

			case EventType::VEHICLE_MOVE_RIGHT:
				GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->Translate(
					GameMaps[CurrentMapID]->m_Entities[PlayerEntityID]->GetTransform()->GetPosition()
					+ glm::vec3(1.0f, 0.0f, 0.0f) * PlayerSpeed * _DeltaTime);
				_EventQueue.pop();
				break;
			default:
				break;
			}
		}
	}
	void GameManager::Terminate()
	{
		for (auto it : GameMaps) {
			for (auto it2 : it.second->m_Entities) {
				delete it2.second;
			}
			delete it.second;
		}
	}
}
