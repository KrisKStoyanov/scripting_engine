#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../Vertex.h"

class GraphicsComponent
{
public:
	GraphicsComponent(std::vector<Vertex> _Verts, std::vector<GLuint> _Indices);
	~GraphicsComponent();

	bool Setup();
	void Clear();

	GLuint ProgramID = 0;
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint IBO = 0;

	GLint PositionAttribID = 0;
	GLint ColorAttribID = 1;

	std::vector<Vertex> VertexCollection;
	std::vector<GLuint> IndexCollection;

	GLuint ModelMatrixLoc;
	glm::mat4 ModelMatrix = glm::mat4(1.0f);
};

