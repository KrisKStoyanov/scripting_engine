#include "Entity.h"

Entity::Entity(glm::vec3 _Position, glm::vec3 _Direction)
{
	Position = _Position;
	Direction = _Direction;
}

Entity::~Entity()
{
}

void Entity::Setup(Mesh* _Mesh, PhysicsComponent* _PSX , AudioComponent* _Audio)
{
	if (_Mesh->Setup()) {
		m_Mesh = _Mesh;
	}
	if (_PSX->Setup()) {
		m_PSX = _PSX;
	}
	if (_Audio->Setup()) {
		m_Audio = _Audio;
	}
}

void Entity::Clear()
{
	if (m_Mesh != NULL) {
		m_Mesh->Clear();
		m_Mesh = nullptr;
	}

	if (m_PSX != NULL) {
		m_PSX->Clear();
		m_PSX = nullptr;
	}

	if (m_Audio != NULL) {
		m_Audio->Clear();
		m_Audio = nullptr;
	}
}

