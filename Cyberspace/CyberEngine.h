#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Entity.h"
#include "Shader.h"
#include "GUI/imgui.h"

enum LocalState {
	STARTING,
	ACTIVE,
	INACTIVE
};

class CyberEngine
{
public:
	CyberEngine();
	~CyberEngine();

	bool Init(const char* _WindowName, unsigned int _WindowWidth, unsigned int _WindowHeight);
	void Start();
	void Configure();
	void Update();
	void Deactivate();
	
	static void GLFW_Error_Callback(int error, const char* description);

	void PrintProgramLog(GLuint _ProgramID);
	void PrintShaderLog(GLuint _ShaderID);

	unsigned int CR_WindowWidth = 800;
	unsigned int CR_WindowHeight = 600;

	GLFWwindow* CR_MainWindow = nullptr;

	LocalState CR_CurrentState = INACTIVE;

	std::map<std::string, Entity*> CR_Entities;

	void AddShader(std::string _ShaderKey, Shader* _TargetShader);
	std::map<std::string, Shader*> CR_Shaders;
};

