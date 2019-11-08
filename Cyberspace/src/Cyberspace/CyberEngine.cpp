#include "CyberEngine.h"

CyberEngine::CyberEngine()
{
}

CyberEngine::~CyberEngine()
{
}


bool CyberEngine::Init(const char* _WindowTitle, int _WindowWidth, int _WindowHeight)
{
	LocalState CurrentState = LocalState::STARTING;

	bool SubsystemStatus;
	E_Window = new EngineWindow(SubsystemStatus, _WindowTitle, _WindowWidth, _WindowHeight);
	if (!SubsystemStatus) {
		printf("Window initialization failed");
		return false;
	}

	E_Renderer = new Renderer(SubsystemStatus, _WindowWidth, _WindowHeight);
	if (!SubsystemStatus) {
		printf("Engine Renderer initialization failed");
		return false;
	}

	E_Physics = new PhysicsSystem(SubsystemStatus);
	if (!SubsystemStatus) {
		printf("Engine Physics initialization failed");
		return false;
	}

	E_Audio = new AudioSystem(SubsystemStatus);
	if (!SubsystemStatus) {
		printf("Engine Audio initialization failed");
		return false;
	}

	E_Net = new CyberNet(SubsystemStatus);
	if (!SubsystemStatus) {
		printf("Engine Network initialization failed");
		return false;
	}

	E_UI = new UISystem(SubsystemStatus);
	if (!SubsystemStatus) {
		printf("Engine Interface initialization failed");
		return false;
	}
	//ImGui::CreateContext();
	//ImGuiIO& IO = ImGui::GetIO();
	//int AtlasWidth, AtlasHeight;
	//unsigned char* AtlasPixels = NULL;
	//IO.Fonts->GetTexDataAsRGBA32(&AtlasPixels, &AtlasWidth, &AtlasHeight); 

	//ImGui::StyleColorsDark();

	//CR_Renderer = new CyberRenderer();
	//CR_Interface = new CyberInterface();
	//CR_Physics = new CyberPhysics();
	//CR_Audio = new CyberAudio();
	//CR_Net = new CyberNet();
	

	Engine_State = LocalState::ACTIVE;
	Configure();
	return 1;
}

void CyberEngine::Configure()
{
	Model* TestModel = new Model("../External Resources/3D/crysisGuy/scene.gltf");
	Entity* TestEntity = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	TestEntity->Configure(TestModel);
	EntityCollection.push_back(TestEntity);

	//Engine_Audio->PlayBGM(0);

	E_Net->CreateServer();
	E_Net->CreateClient();
	E_Net->ConnectToHost();

	//Game = new GameInstance();
	//Game->Start();

	EventQueue.push(new CyberEvent(EventType::START));

	Update();
}

float CyberEngine::ComputeDeltaTime(float _CurrentFrameTime)
{
	DeltaTime = _CurrentFrameTime - LastFrameTime;
	LastFrameTime = _CurrentFrameTime;
	return DeltaTime;
}

void CyberEngine::Update()
{
	double CursorPosX, CursorPosY;
	while (E_Window->Active) {
		E_Window->Update(EventQueue, CursorPosX, CursorPosY);
		E_Renderer->Update(EventQueue, EntityCollection, CursorPosX, CursorPosY, ComputeDeltaTime(glfwGetTime()));
		//Engine_Physics->Update(EventQueue, EntityCollection);
		//	
		//	//ImGui::NewFrame();
		//	//ImGui::Render();

		//	//while (Engine_Net->UpdateServer()) {

		//	//}
		//}
	}
	Terminate();
}

void CyberEngine::Terminate()
{
	Engine_State = LocalState::INACTIVE;
	E_Window->Terminate();
	E_Renderer->Terminate();
	E_Physics->Terminate();
	E_Audio->Terminate();
	E_Net->Terminate();
	E_UI->Terminate();
	//ImGui::DestroyContext(); 
	delete E_Renderer;
	delete E_Physics;
	delete E_Audio;
	delete E_Net;
	delete E_UI;
	delete E_Window;
}

