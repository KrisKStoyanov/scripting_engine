#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../Vertex.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex> _VertexCollection, std::vector<GLuint> _IndexCollection);
	~Mesh();

	bool Setup();
	void Clear();

	GLuint ProgramID = 0, VAO = 0, VBO = 0, IBO = 0;

	GLint PositionAttribID = 0, ColorAttribID = 1;

	std::vector<Vertex> VertexCollection;
	std::vector<GLuint> IndexCollection;

	glm::mat4 ModelMatrix = glm::mat4(1.0f);
};

