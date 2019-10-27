#include "CyberRenderer.h"

CyberRenderer::CyberRenderer(bool& _InitStatus, const char* _WindowTitle, int _WindowWidth, int _WindowHeight)
{
	_InitStatus = Init(_WindowTitle,_WindowWidth, _WindowHeight);
}

CyberRenderer::~CyberRenderer()
{
}

void CyberRenderer::GLFW_Error_Callback(int _Error, const char* _Description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", _Error, _Description);
}

bool CyberRenderer::Init(const char* _WindowTitle, int _WindowWidth, int _WindowHeight)
{
	glfwSetErrorCallback(GLFW_Error_Callback);

	if (!glfwInit()) {
		return false;
	}

	CR_WindowWidth = _WindowWidth;
	CR_WindowHeight = _WindowHeight;
	CR_MainWindow = glfwCreateWindow(_WindowWidth, _WindowHeight, _WindowTitle, NULL, NULL);

	if (!CR_MainWindow) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(CR_MainWindow);

	glewExperimental = GL_TRUE;
	GLenum initState = glewInit();

	if (initState != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(initState));
		return false;
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	//Anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Configure();
	return true;
}

void CyberRenderer::Configure()
{
	Shader* TestShader = new Shader("./Shaders/vert.glsl", "./Shaders/frag.glsl");
	CR_Shaders["TestShader"] = TestShader;
}

void CyberRenderer::Update(std::map<std::string, Entity*> _EntityCollection)
{
	while (!glfwWindowShouldClose(CR_MainWindow)) {
		CR_Shaders["TestShader"]->Activate();
		for (std::pair<std::string, Entity*> E : _EntityCollection) {
			glBindVertexArray(E.second->VAO);
			glDrawElements(GL_TRIANGLES, E.second->IndexCollection.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		CR_Shaders["TestShader"]->Deactivate();
		glfwSwapBuffers(CR_MainWindow);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void CyberRenderer::Terminate()
{
	for (std::pair<std::string, Shader*> S : CR_Shaders) {
		S.second->Clear();
	}

	glfwDestroyWindow(CR_MainWindow);
	glfwTerminate();
}

void CyberRenderer::AddShader(std::string _ShaderKey, Shader* _TargetShader)
{
	CR_Shaders[_ShaderKey] = _TargetShader;
}

void CyberRenderer::PrintProgramLog(GLuint _ProgramID)
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

void CyberRenderer::PrintShaderLog(GLuint _ShaderID)
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
