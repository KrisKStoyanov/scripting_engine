#include "cspacepch.h"
#include "CyberEngine.h"

namespace Cyberspace {
	CyberEngine* Cyberspace::CyberEngine::Create(const EngineProps& _props)
	{
		return new CyberEngine(_props);
	}

	CyberEngine::CyberEngine(const EngineProps& _props)
	{
		m_Props = _props;
		Init(_props);
	}

	CyberEngine::~CyberEngine()
	{
		Terminate();
	}


	void CyberEngine::Init(const EngineProps& _props)
	{
		//OGL, GLFW, Dear ImGUI:
		m_Window = std::unique_ptr<EngineWindow>(EngineWindow::Create(_props.m_GraphicsProps));
		m_Renderer = std::unique_ptr<Renderer>(Renderer::Create(_props.m_GraphicsProps));
		m_GUI = std::unique_ptr<GUIToolkit>(GUIToolkit::Create(m_Window.get(),_props.m_GraphicsProps));

		//PhysX:
		m_PhysicsSystem = std::unique_ptr<PhysicsSystem>(PhysicsSystem::Create(_props.m_PhysicsProps));
		
		//Fmod:
		m_AudioSystem = std::unique_ptr<AudioSystem>(AudioSystem::Create(_props.m_AudioProps));
		
		//Enet
		m_NetSystem = std::unique_ptr<CyberNet>(CyberNet::Create(_props.m_NetProps));
		
		//Assimp
		m_AssetManager = std::unique_ptr<AssetManager>(AssetManager::Create(_props.m_AMProps));

		//------
		m_GameManager = std::unique_ptr<GameManager>(GameManager::Create(m_AssetManager->LoadedModels, _props.m_GMProps));

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
		//CSPACE_CORE_TRACE("Delta time: {0}s ({1}ms)", _ts.GetSeconds(), _ts.GetMilliseconds());
		std::vector<glm::vec3> updatedPositions;
		m_Window->OnUpdate(BlockingEventQueue, EventQueue);
		m_Renderer->OnUpdate(BlockingEventQueue, EventQueue, 
			m_AssetManager->LoadedShaders,
			m_GameManager->GameMaps[m_GameManager->CurrentMapID]->m_Entities,
			m_Window->CursorPosX, m_Window->CursorPosY, _ts.GetSeconds());
		m_GUI->OnUpdate(BlockingEventQueue, EventQueue, m_Props);
		m_GameManager->OnUpdate(EventQueue, _ts.GetSeconds());
		if (m_Props.m_NetProps.m_ClientState == ClientState::Connected) {
			m_NetSystem->OnUpdate(EventQueue, updatedPositions);
		}
		
		if (!BlockingEventQueue.empty()) {
			switch (BlockingEventQueue.front()->Type) {
			case EventType::CONNECT:
				m_Props.m_NetProps.m_ClientState = ClientState::Connected;
				m_NetSystem->ConnectToHost();
				BlockingEventQueue.pop();
				break;
			case EventType::START:
				m_Window->Configure(m_Props.m_GraphicsProps);
				m_Renderer->SetCameraMovement(true);
				BlockingEventQueue.pop();
				break;
			case EventType::PAUSE:
				m_Props.m_GraphicsProps.m_EnCursor = true;
				m_Props.m_GMProps.Paused = true;
				m_Window->Configure(m_Props.m_GraphicsProps);
				m_Renderer->SetCameraMovement(false);
				BlockingEventQueue.pop();
				break;
			case EventType::RESUME:
				m_Window->Configure(m_Props.m_GraphicsProps);
				m_Renderer->SetCameraMovement(true);
				BlockingEventQueue.pop();
				break;
			case EventType::UPDATE_SETTINGS:
				m_Window->Recreate(m_Props.m_GraphicsProps);
				m_Renderer->Restart(m_Props.m_GraphicsProps, m_AssetManager->LoadedModels);
				BlockingEventQueue.pop();
				break;
			case EventType::EXIT:
				SetTick(false);
				BlockingEventQueue.pop();
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
		m_GUI.reset();
		m_Renderer.reset();
		m_Window.reset();
		m_PhysicsSystem.reset();
		m_PhysicsSystem.reset();
		m_AudioSystem.reset();
		m_NetSystem.reset();
	}
}


