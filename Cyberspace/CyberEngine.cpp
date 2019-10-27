#include "CyberEngine.h"

CyberEngine::CyberEngine()
{
}

CyberEngine::~CyberEngine()
{
}


bool CyberEngine::Init(const char* _WindowTitle, int _WindowWidth, int _WindowHeight)
{
	LocalState CurrentState = STARTING;

	bool SubsystemStatus;

	Engine_Renderer = new CyberRenderer(SubsystemStatus, _WindowTitle, _WindowWidth, _WindowHeight);
	if (!SubsystemStatus) {
		printf("Engine Renderer initialization failed");
		return false;
	}

	Engine_Physics = new CyberPhysics(SubsystemStatus);
	if (!SubsystemStatus) {
		printf("Engine Physics initialization failed");
		return false;
	}

	Engine_Audio = new CyberAudio(SubsystemStatus);
	if (!SubsystemStatus) {
		printf("Engine Audio initialization failed");
		return false;
	}

	Engine_Net = new CyberNet(SubsystemStatus);
	if (!SubsystemStatus) {
		printf("Engine Network initialization failed");
		return false;
	}

	Engine_Interface = new CyberInterface(SubsystemStatus);
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
	Engine_State = ACTIVE;
	Configure();
	return 1;
}

void CyberEngine::Configure()
{

	Engine_Audio->PlayBGM(0);

	Engine_Net->CreateServer();
	Engine_Net->CreateClient();
	Engine_Net->ConnectToHost();

	Game = new GameInstance(Engine_Renderer->CR_MainWindow);
	Game->Start();

	Update();
}

void CyberEngine::Update()
{
	
	while(Engine_State == 1){
		//glfwWindowShouldClose(CR_MainWindow)
		glfwPollEvents();
		Engine_Renderer->Update(Game->EntityCollection);
		
		//ImGui::NewFrame();
		//ImGui::Render();

		while (Engine_Net->UpdateServer()) {

		}

	}
	Deactivate();
}

void CyberEngine::ProcessInput()
{
}

void CyberEngine::Deactivate()
{
	Engine_State = INACTIVE;
	Engine_Renderer->Terminate();
	Engine_Physics->Terminate();
	Engine_Audio->Terminate();
	Engine_Net->Terminate();
	Engine_Interface->Terminate();
	//ImGui::DestroyContext(); 
	delete Engine_Renderer;
	delete Engine_Physics;
	delete Engine_Audio;
	delete Engine_Net;
	delete Engine_Interface;
}

