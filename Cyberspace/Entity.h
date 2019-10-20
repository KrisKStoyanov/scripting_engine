#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vertex.h"
#include "Shader.h"

class Entity
{
public:
	Entity(std::vector<Vertex> _Verts, std::vector<GLuint> _Indices);
	~Entity();

	void Setup();
	void Clear();

	GLuint ProgramID = 0;
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint IBO = 0;

	GLint PositionAttribID = 0;
	GLint ColorAttribID = 1;

	std::vector<Vertex> VertexCollection;
	std::vector<GLuint> IndexCollection;
};

