#include "Entity.h"

namespace Cyberspace {
	Entity::Entity(glm::vec3 _Position, glm::vec3 _Direction)
	{
		Position = _Position;
		Direction = _Direction;
	}

	Entity::~Entity()
	{
	}

	void Entity::Configure(Model* _Model, PhysicsComponent* _PSX, AudioComponent* _Audio)
	{
		m_Model = _Model;
		if (_PSX->Setup()) {
			m_PSX = _PSX;
		}
		if (_Audio->Setup()) {
			m_Audio = _Audio;
		}
	}

	void Entity::Clear()
	{
		if (m_Model != NULL) {
			for (int i = 0; i < m_Model->Meshes.size(); ++i) {
				m_Model->Meshes[i].Clear();
			}
			m_Model = nullptr;
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
}


