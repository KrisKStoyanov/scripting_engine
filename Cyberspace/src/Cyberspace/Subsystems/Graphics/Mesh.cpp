#include "Mesh.h"

namespace Cyberspace {
	Mesh::Mesh(std::vector<Vertex> _VertexCollection, std::vector<GLuint> _IndexCollection, std::vector<Texture> _TextureCollection) {
		VertexCollection = _VertexCollection;
		IndexCollection = _IndexCollection;
		TextureCollection = _TextureCollection;
		Setup();
	}

	Mesh::~Mesh() {

	}

	bool Mesh::Setup() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, VertexCollection.size() * sizeof(Vertex), VertexCollection.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCollection.size() * sizeof(GLuint), IndexCollection.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(PositionAttribID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(PositionAttribID);
		glVertexAttribPointer(NormalAttribID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(VertexCollection[0].Position));
		glEnableVertexAttribArray(NormalAttribID);
		glVertexAttribPointer(TextureAttribID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(VertexCollection[0].Position) + sizeof(VertexCollection[0].Normal)));
		glEnableVertexAttribArray(TextureAttribID);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(PositionAttribID);
		glDisableVertexAttribArray(NormalAttribID);
		glDisableVertexAttribArray(TextureAttribID);

		return true;
	}

	void Mesh::Clear() {
		glDisableVertexAttribArray(0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &IBO);
	}
}
