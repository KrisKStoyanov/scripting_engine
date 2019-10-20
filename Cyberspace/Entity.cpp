#include "Entity.h"

Entity::Entity(std::vector<Vertex> _Verts, std::vector<GLuint> _Indices)
{
	VertexCollection = _Verts;
	IndexCollection = _Indices;
}

Entity::~Entity()
{
}

void Entity::Setup()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VertexCollection.size() * sizeof(Vertex), VertexCollection.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCollection.size() * sizeof(GLuint), IndexCollection.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(PositionAttribID, 3, GL_FLOAT, GL_FALSE, sizeof(VertexCollection[0]), (void*)0);
	glEnableVertexAttribArray(PositionAttribID);
	glVertexAttribPointer(ColorAttribID, 4, GL_FLOAT, GL_FALSE, sizeof(VertexCollection[0]), (GLvoid*)sizeof(VertexCollection[0].Position));
	glEnableVertexAttribArray(ColorAttribID);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(PositionAttribID);
	glDisableVertexAttribArray(ColorAttribID);
}

void Entity::Clear()
{
	glDisableVertexAttribArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

