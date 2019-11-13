#include "Entity.h"

namespace Cyberspace {
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
		Clear();
	}

	void Entity::Clear()
	{
		if (m_Transform != NULL) {
			m_Transform = nullptr;
		}

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


