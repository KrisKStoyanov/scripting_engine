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

		//ImGui::CreateContext();
		//ImGuiIO& IO = ImGui::GetIO();
		//int AtlasWidth, AtlasHeight;
		//unsigned char* AtlasPixels = NULL;
		//IO.Fonts->GetTexDataAsRGBA32(&AtlasPixels, &AtlasWidth, &AtlasHeight); 

		//ImGui::StyleColorsDark();
		m_Running = true;
	}

	void CyberEngine::Configure()
	{
		Model* TestModel = new Model("../External Resources/3D/crysisGuy/scene.gltf");
		Entity* TestEntity = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		TestEntity->Configure(TestModel);
		EntityCollection.push_back(TestEntity);

		//Engine_Audio->PlayBGM(0);

		//E_Net->CreateServer();
		//E_Net->CreateClient();
		//E_Net->ConnectToHost();

		EventQueue.push(new CyberEvent(EventType::START));
	}

	float CyberEngine::ComputeDeltaTime(float _CurrentFrameTime)
	{
		DeltaTime = _CurrentFrameTime - LastFrameTime;
		LastFrameTime = _CurrentFrameTime;
		return DeltaTime;
	}

	void CyberEngine::OnUpdate()
	{
		double CursorPosX, CursorPosY;
		m_Window->Update(EventQueue, CursorPosX, CursorPosY);
		m_Renderer->Update(EventQueue, EntityCollection, CursorPosX, CursorPosY, ComputeDeltaTime(glfwGetTime()));


		if (!EventQueue.empty()) {
			switch (EventQueue.front()->Type) {
			case EventType::START:
				printf("START EVENT\n");
				EventQueue.pop();
				break;
			case EventType::EXIT:
				printf("EXIT EVENT\n");
				m_Running = false;
				EventQueue.pop();
				break;
			default:
				break;
			}
		}
	}

	void CyberEngine::Terminate()
	{
		m_Window.reset();
		m_Renderer.reset();
		m_PhysicsSystem.reset();
		m_AudioSystem.reset();
		m_NetSystem.reset();
		m_UISystem.reset();
		//ImGui::DestroyContext(); 
	}
}


