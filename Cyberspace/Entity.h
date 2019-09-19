#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	void Setup();
	void Render();

	//GLuint ProgramID = 0;
	//GLuint VBO = 0;
	//GLuint IBO = 0;

	//GLuint VertShader;

};

