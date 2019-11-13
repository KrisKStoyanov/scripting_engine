#include "Entity.h"

namespace Cyberspace {
	Entity::Entity(Transform* _transform, EntityTag _tag)
	{
		m_Transform = _transform;
		m_Tag = _tag;
	}

	Entity::~Entity()
	{
		Clear();
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


