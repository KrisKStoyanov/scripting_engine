#include "CyberEngine.h"

CyberEngine::CyberEngine()
{
}

CyberEngine::~CyberEngine()
{
}

void CyberEngine::GLFW_Error_Callback(int _Error, const char* _Description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", _Error, _Description);
}

bool CyberEngine::Init(const char* _WindowTitle, int _WindowWidth, int _WindowHeight)
{
	LocalState CurrentState = STARTING;

	glfwSetErrorCallback(GLFW_Error_Callback);
	if (!glfwInit()) {
		return 0;
	}

	//RENDERER SUBSYSTEM:

	//WINDOW CREATION: (POWERED BY GLFW)
	CR_WindowWidth = _WindowWidth;
	CR_WindowHeight = _WindowHeight;
	CR_MainWindow = glfwCreateWindow(_WindowWidth, _WindowHeight, _WindowTitle, NULL, NULL);
	if (!CR_MainWindow) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(CR_MainWindow);

	//ANTI-ALIASING SETTINGS
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//OGL INTERFACE PROVIDER (POWERED BY GLEW)
	glewExperimental = GL_TRUE;
	GLenum initState = glewInit();

	if (initState != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(initState));
		return 0;
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	//ImGui::CreateContext();
	//ImGuiIO& IO = ImGui::GetIO();
	//int AtlasWidth, AtlasHeight;
	//unsigned char* AtlasPixels = NULL;
	//IO.Fonts->GetTexDataAsRGBA32(&AtlasPixels, &AtlasWidth, &AtlasHeight); 

	//ImGui::StyleColorsDark();

	glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
	//glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	Start();
	return 1;
}

void CyberEngine::Configure()
{
	CR_Renderer = new CyberRenderer();
	CR_Interface = new CyberInterface();
	CR_Physics = new CyberPhysics();
	CR_Audio = new CyberAudio();
	CR_Net = new CyberNet();

	CR_Renderer->Activate();
	CR_Audio->Activate();
	CR_Net->Activate();

	Game = new GameInstance(CR_MainWindow);
}

void CyberEngine::Start()
{
	CR_CurrentState = ACTIVE;
	Configure();
	CR_Net->CreateServer();
	CR_Net->CreateClient();
	CR_Net->ConnectToHost();
	CR_Audio->PlayBGM(0);
	Game->Start();
	Update();
}

void CyberEngine::Update()
{
	while(CR_CurrentState == 1){
		//glfwWindowShouldClose(CR_MainWindow)
		glfwPollEvents();
		for (std::pair<std::string, Entity*> E : Game->EntityCollection) {
			CR_Renderer->Update(E.second);
		}
		
		//ImGui::NewFrame();
		//ImGui::Render();
		glfwSwapBuffers(CR_MainWindow);
		glClear(GL_COLOR_BUFFER_BIT);

		CR_Audio->Update();

		while (CR_Net->UpdateServer()) {

		}
	}
	Deactivate();
}

void CyberEngine::ProcessInput()
{
}

void CyberEngine::Deactivate()
{
	CR_CurrentState = INACTIVE;
	CR_Renderer->Deactivate();
	CR_Net->Deactivate();
	CR_Interface->Deactivate();
	CR_Physics->Deactivate();
	CR_Audio->Deactivate();
	//ImGui::DestroyContext(); 
	delete CR_Renderer;
	glfwDestroyWindow(CR_MainWindow);
	glfwTerminate();
}

