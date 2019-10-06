#include "CyberEngine.h"

CyberEngine::CyberEngine()
{
}

CyberEngine::~CyberEngine()
{
}

void CyberEngine::GLFW_Error_Callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool CyberEngine::Init(const char* _WindowName, unsigned int _WindowWidth, unsigned int _WindowHeight)
{
	LocalState CurrentState = STARTING;
	CR_WindowWidth = _WindowWidth;
	CR_WindowHeight = _WindowHeight;

	glfwSetErrorCallback(GLFW_Error_Callback);
	if (!glfwInit()) {
		return 0;
	}

	//Antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	CR_MainWindow = glfwCreateWindow(_WindowWidth, _WindowHeight, _WindowName, NULL, NULL);

	if (!CR_MainWindow) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(CR_MainWindow);

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

	return 1;
}

void CyberEngine::Start()
{
	CR_CurrentState = ACTIVE;
	Configure();
	Update();
}

void CyberEngine::Configure()
{
	std::vector<Vertex> EntityVerts({
		{{ 0.5f,  0.5f, 0.0f, }, {1.0f, 0.0f, 0.0f, 1.0f }},
		{{ 0.5f, -0.5f, 0.0f, }, {1.0f, 1.0f, 0.0f, 1.0f }},
		{{ -0.5f, -0.5f, 0.0f, }, {1.0f, 0.0f, 1.0f, 1.0f }},
		{{ -0.5f,  0.5f, 0.0f }, {0.0f, 1.0f, 1.0f, 1.0f }}
		});
	std::vector<GLuint> EntityIndices({ 0,1,3, 1,2,3 });

	Entity* TestEntity = new Entity(EntityVerts, EntityIndices);

	TestEntity->Setup();
	CR_Entities["TestEntity"] = TestEntity;

	Shader* TestShader = new Shader("./Shaders/vert.glsl", "./Shaders/frag.glsl");
	CR_Shaders["TestShader"] = TestShader;
}

void CyberEngine::Update()
{
	while(!glfwWindowShouldClose(CR_MainWindow)){
		
		glfwPollEvents();

		CR_Entities["TestEntity"]->Render(CR_Shaders["TestShader"]);
		//ImGui::NewFrame();
		//ImGui::Render();
		glfwSwapBuffers(CR_MainWindow);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void CyberEngine::Deactivate()
{
	CR_Shaders["TestShader"]->Clear();
	//ImGui::DestroyContext(); 
	glfwTerminate();
}

void CyberEngine::PrintProgramLog(GLuint _ProgramID)
{
	if (glIsProgram(_ProgramID)) {
		int InfoLogLength = 0;
		int MaxLength = InfoLogLength;

		glGetProgramiv(_ProgramID, GL_INFO_LOG_LENGTH, &MaxLength);

		char* InfoLog = new char[MaxLength];

		glGetProgramInfoLog(_ProgramID, MaxLength, &InfoLogLength, InfoLog);
		if (InfoLogLength > 0) {
			fprintf(stdout, "%s\n", InfoLog);
		}

		delete[] InfoLog;
	}
	else {
		fprintf(stdout, "%d is not a valid program ID\n", _ProgramID);
	}
}

void CyberEngine::PrintShaderLog(GLuint _ShaderID)
{
	if (glIsShader(_ShaderID)) {
		int InfoLogLength = 0;
		int MaxLength = InfoLogLength;

		glGetShaderiv(_ShaderID, GL_INFO_LOG_LENGTH, &MaxLength);

		char* InfoLog = new char[MaxLength];

		glGetShaderInfoLog(_ShaderID, MaxLength, &InfoLogLength, InfoLog);
		if (InfoLogLength > 0) {
			fprintf(stdout, "%s\n", InfoLog);
		}

		delete[] InfoLog;
	}
	else {
		fprintf(stdout, "%d is not a valid shader ID\n", _ShaderID);
	}
}

void CyberEngine::AddShader(std::string _ShaderKey, Shader* _TargetShader)
{
	CR_Shaders[_ShaderKey] = _TargetShader;
}
