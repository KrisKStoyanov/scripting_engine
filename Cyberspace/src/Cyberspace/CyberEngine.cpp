#include "../cspacepch.h"
#include "CyberEngine.h"

namespace Cyberspace {
	CyberEngine* Cyberspace::CyberEngine::Create(const EngineProps& _props)
	{
		return new CyberEngine(_props);
	}

	CyberEngine::CyberEngine(const EngineProps& _props)
	{
		Init(_props);
	}

	CyberEngine::~CyberEngine()
	{
		Terminate();
	}


	void CyberEngine::Init(const EngineProps& _props)
	{
		m_UIController = std::unique_ptr<UIController>(UIController::Create(_props.m_UIProps));
		m_Renderer = std::unique_ptr<Renderer>(Renderer::Create(_props.m_GraphicsProps));
		m_GUIToolkit = std::unique_ptr<GUIToolkit>(
			GUIToolkit::Create(GUIProps(m_UIController->AvailableWindows[_props.m_UIProps.windowProps.Title])));
		m_PhysicsSystem = std::unique_ptr<PhysicsSystem>(PhysicsSystem::Create(_props.m_PhysicsProps));
		m_AudioSystem = std::unique_ptr<AudioSystem>(AudioSystem::Create(_props.m_AudioProps));
		m_NetSystem = std::unique_ptr<CyberNet>(CyberNet::Create(_props.m_NetProps));
		m_AssetManager = std::unique_ptr<AssetManager>(AssetManager::Create(_props.m_AMProps));
		m_GameManager = std::unique_ptr<GameManager>(GameManager::Create(_props.m_GMProps));

		m_GameManager->PlayerEntity->SetModel(m_AssetManager->LoadedModels[_props.m_GMProps.PlayerModelTag]);

		//m_AudioSystem->PlayBGM(0);
		//m_GameManager->PlayerEntity = new Entity();
		//m_GameManager->PlayerEntity->SetTransform(new Transform());
		//m_GameManager->PlayerEntity->SetModel(m_AssetManager->LoadedModels[_props.m_GMProps.PlayerModelTag]);
		//m_GameManager->PlayerSpeed = _props.m_GMProps.PlayerSpeed;
		//m_GameManager->GameMaps[_props.m_GMProps.StartMapTag]->MapEntities[_props.m_GMProps.PlayerTag] 
		//	= m_GameManager->PlayerEntity;

		m_Tick = true;
	}

	void CyberEngine::OnUpdate(const Timestep _ts)
	{
		CSPACE_CORE_TRACE("Delta time: {0}s ({1}ms)", _ts.GetSeconds(), _ts.GetMilliseconds());
		std::vector<glm::vec3> updatedPositions;
		m_UIController->OnUpdate(BlockingEventQueue, EventQueue);
		m_Renderer->OnUpdate(
			EventQueue, m_AssetManager->LoadedShaders,
			m_GameManager->GameMaps[m_GameManager->CurrentMap]->MapEntities,
			m_UIController->CursorPosX, m_UIController->CursorPosY, _ts.GetSeconds());
		m_GUIToolkit->OnUpdate(BlockingEventQueue, EventQueue);
		m_NetSystem->OnUpdate(EventQueue, updatedPositions);
		
		if (!BlockingEventQueue.empty()) {
			switch (BlockingEventQueue.front()->Type) {
			case EventType::EXIT:
				Terminate();
				break;
			case EventType::PAUSE:
				break;
			default:
				break;
			}
		}
	}

	void CyberEngine::Terminate()
	{
		while (!BlockingEventQueue.empty()) {
			BlockingEventQueue.pop();
		}
		while (!EventQueue.empty()) {
			EventQueue.pop();
		}
		m_GameManager.reset();
		m_AssetManager.reset();
		m_UIController.reset();
		m_Renderer.reset();
		m_PhysicsSystem.reset();
		m_PhysicsSystem.reset();
		m_AudioSystem.reset();
		m_NetSystem.reset();
	}
}


