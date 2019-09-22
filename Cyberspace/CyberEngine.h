#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Entity.h";
#include "Shader.h"

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

	bool Init(std::string _WindowName, unsigned int _WindowWidth, unsigned int _WindowHeight, SDL_RendererFlags _RenderingFlag);
	void Start();
	void PrintOGLVersion();
	void CheckSDLError(int line);
	void Configure();
	void Update();
	void Deactivate();

	void PrintProgramLog(GLuint _ProgramID);
	void PrintShaderLog(GLuint _ShaderID);

	unsigned int CR_WindowWidth = 800;
	unsigned int CR_WindowHeight = 600;

	SDL_Window* CR_MainWindow = nullptr;

	SDL_GLContext CR_OGL_Context = NULL;
	LocalState CR_CurrentState = INACTIVE;

	std::map<std::string, Entity*> CR_Entities;

	void AddShader(std::string _ShaderKey, Shader* _TargetShader);
	std::map<std::string, Shader*> CR_Shaders;
};

