#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	unsigned int CR_WindowWidth;
	unsigned int CR_WindowHeight;

	SDL_Window* CR_MainWindow = nullptr;

	SDL_GLContext CR_OGL_Context;
	LocalState CR_CurrentState;
};

