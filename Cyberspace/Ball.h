#pragma once
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball();

	virtual Entity* Clone(glm::vec3 _Position) {
		return new Ball(_Position, Speed);
	}

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

private:
	glm::vec3 Position;
	float Speed;
};

