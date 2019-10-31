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
	Engine_Window = new CyberWindow(SubsystemStatus, _WindowTitle, _WindowWidth, _WindowHeight);
	if (!SubsystemStatus) {
		printf("Window initialization failed");
		return false;
	}

	Engine_Renderer = new CyberRenderer(SubsystemStatus, _WindowWidth, _WindowHeight);
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
	

	Engine_State = LocalState::ACTIVE;
	Configure();
	return 1;
}

void CyberEngine::Configure()
{
	Entity* TestCube = new Entity(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f,0.f,0.f));
	std::vector<Vertex> VertexCollection({
	{{ 0.5f,  0.5f, 0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f }},
	{{ 0.5f, -0.5f, 0.5f, 1.0f }, {1.0f, 1.0f, 0.0f, 1.0f }},
	{{ -0.5f, -0.5f, 0.5f, 1.0f }, {1.0f, 0.0f, 1.0f, 1.0f }},
	{{ -0.5f,  0.5f, 0.5f, 1.0f }, {0.0f, 1.0f, 1.0f, 1.0f }},
	{{ 0.5f,  0.5f, -0.5f, 1.0f }, {1.0f, 0.0f, 0.0f, 1.0f }},
	{{ 0.5f, -0.5f, -0.5f, 1.0f }, {1.0f, 1.0f, 0.0f, 1.0f }},
	{{ -0.5f, -0.5f, -0.5f, 1.0f }, {1.0f, 0.0f, 1.0f, 1.0f }},
	{{ -0.5f,  0.5f, -0.5f, 1.0f }, {0.0f, 1.0f, 1.0f, 1.0f }}
		});
	std::vector<GLuint> IndexCollection({ 
		0,1,3, 1,2,3, //FRONT
		0,3,4, 4,7,3, //LEFT
		1,2,5, 5,6,2, //RIGHT
		3,2,7, 7,6,2, //TOP
		0,1,4, 4,5,1,//BOTTOM
		4,5,7, 5,6,7 //BACK
		});
	TestCube->Setup(new GraphicsComponent(VertexCollection, IndexCollection), new PhysicsComponent());

	EntityCollection.push_back(TestCube);
	Engine_Renderer->TestEntity = EntityCollection.front();

	//Engine_Audio->PlayBGM(0);

	Engine_Net->CreateServer();
	Engine_Net->CreateClient();
	Engine_Net->ConnectToHost();

	//Game = new GameInstance();
	//Game->Start();

	EventQueue.push(new CyberEvent(EventType::START));

	Update();
}

void CyberEngine::Update()
{
	while (!glfwWindowShouldClose(Engine_Window->PlatformWindow)) {
		Engine_Window->Update(EventQueue);
		Engine_Renderer->Update(EventQueue, EntityCollection);
		Engine_Physics->Update(EntityCollection);
		Engine_Audio->Update(EntityCollection);
		Engine_Interface->Update();		
		//	
		//	//ImGui::NewFrame();
		//	//ImGui::Render();

		//	//while (Engine_Net->UpdateServer()) {

		//	//}
		//}
	}
	Deactivate();
}

void CyberEngine::Deactivate()
{
	Engine_State = LocalState::INACTIVE;
	Engine_Window->Terminate();
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
	delete Engine_Window;
}

