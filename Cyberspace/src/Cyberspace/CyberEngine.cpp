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
		m_Window = std::unique_ptr<EngineWindow>(EngineWindow::Create(_props.m_WindowProps));
		m_Renderer = std::unique_ptr<Renderer>(Renderer::Create(_props.m_GraphicsProps));
		m_PhysicsSystem = std::unique_ptr<PhysicsSystem>(PhysicsSystem::Create(_props.m_PhysicsProps));
		m_AudioSystem = std::unique_ptr<AudioSystem>(AudioSystem::Create(_props.m_AudioProps));
		m_UISystem = std::unique_ptr<UISystem>(UISystem::Create(_props.m_UIProps));
		m_NetSystem = std::unique_ptr<CyberNet>(CyberNet::Create(_props.m_NetProps));
		m_AssetManager = std::unique_ptr<AssetManager>(AssetManager::Create(_props.m_AMProps));
		m_GameManager = std::unique_ptr<GameManager>(GameManager::Create(_props.m_GMProps));
		m_Running = true;
	}

	void CyberEngine::Configure()
	{
		Entity* MainEntity = new Entity(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -1.0f), EntityTag::MainCharacter);
		MainEntity->Configure(m_AssetManager->LoadedModels["Vehicle"]);
		EntityCollection.insert(std::pair<EntityTag, Entity*>(MainEntity->m_Tag, MainEntity));

		//Engine_Audio->PlayBGM(0);

		//EventQueue.push(new CyberEvent(EventType::START));
	}

	float CyberEngine::ComputeDeltaTime(float _CurrentFrameTime)
	{
		DeltaTime = _CurrentFrameTime - LastFrameTime;
		LastFrameTime = _CurrentFrameTime;
		return DeltaTime;
	}

	void CyberEngine::OnUpdate()
	{
		double cursorPosX, cursorPosY;
		std::vector<glm::vec3> updatedPositions;
		m_Window->OnUpdate(m_Running, EventQueue, cursorPosX, cursorPosY);
		m_Renderer->OnUpdate(EventQueue, m_AssetManager->LoadedShaders, EntityCollection, cursorPosX, cursorPosY, updatedPositions, ComputeDeltaTime(glfwGetTime()));
		m_NetSystem->OnUpdate(EventQueue, updatedPositions);
	}

	void CyberEngine::Terminate()
	{
		for (std::pair<EntityTag, Entity*> iter : EntityCollection) {
			delete iter.second;
		}
		m_Window.reset();
		m_Renderer.reset();
		m_PhysicsSystem.reset();
		m_AudioSystem.reset();
		m_NetSystem.reset();
		m_UISystem.reset();
	}
}


