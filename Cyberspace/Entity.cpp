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
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, VertexCollection.size() * sizeof(Vertex), VertexCollection.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(PositionAttribID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(PositionAttribID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, VertexCollection.size() * sizeof(Vertex), VertexCollection.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(ColorAttribID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ColorAttribID);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

void Entity::Render(Shader* _RenderingShader)
{
	_RenderingShader->Activate();
	glDrawElements(GL_TRIANGLE_STRIP, IndexCollection.size(), GL_UNSIGNED_INT, nullptr);
}

void Entity::Clear()
{
	glDisableVertexAttribArray(0);
	glDeleteBuffers(2, VBO);
	glDeleteVertexArrays(1, &VAO);
}

