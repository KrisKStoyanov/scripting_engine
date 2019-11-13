#include "Transform.h"

namespace Cyberspace {
	Transform::Transform(glm::vec3 _position, glm::vec3 _orientation)
	{
		m_Position = _position;
		m_Orientation = _orientation;
	}

	Transform::~Transform()
	{
	}
	void Transform::Translate(glm::vec3 _translation)
	{
		//Update position
		m_Position = _translation;
		//Set to identity matrix
		m_ModelMatrix = glm::mat4(1.0f);
		//Move object through matrix set with the argument vector
		m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	}
	void Transform::Translate()
	{
		Translate(m_Position);
	}
	void Transform::Rotate(glm::vec3 _eulerAngles)
	{
	}
	void Transform::LookAt(Transform _target, glm::vec3 _worldUp)
	{
	}
}
