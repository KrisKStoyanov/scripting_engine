#include "cspacepch.h"
#include "Transform.h"

namespace Cyberspace {
	Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		m_Position = _position;
		m_Rotation = _rotation;
		m_Scale = _scale;
	}

	Transform::~Transform()
	{
	}
	void Transform::Translate(glm::vec3 _translation)
	{
		//Update position
		m_Position = _translation;
		m_TranslationMatrix = glm::mat4(1.0f);
		//Move object through matrix set with the argument vector
		m_TranslationMatrix = glm::translate(m_TranslationMatrix, m_Position);
		m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScalingMatrix;
	}
	void Transform::Rotate(float _angleX, float _angleY, float _angleZ)
	{
		m_RotationMatrix = glm::mat4(1.0f);

		//glm::mat4 rotMatX = glm::mat4(1.0f);
		//glm::mat4 rotMatY = glm::mat4(1.0f);
		//glm::mat4 rotMatZ = glm::mat4(1.0f);

		m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(_angleX), glm::vec3(1.0f, 0.0f, 0.0f));
		m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(_angleY), glm::vec3(0.0f, 1.0f, 0.0f));
		m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));

		//m_RotationMatrix = rotMatX * rotMatY * rotMatZ;
		Translate(m_Position);
	}
	void Transform::OnUpdate()
	{
		m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScalingMatrix;
	}
	void Transform::Scale(glm::vec3 _scalingRatio)
	{
		m_ScalingMatrix = glm::scale(m_ScalingMatrix, _scalingRatio);
	}
	void Transform::LookAt(Transform _target, glm::vec3 _worldUp)
	{
	}

	glm::mat4 Transform::RotationMatrix(glm::vec3 axis, float angle)
	{
		axis = normalize(axis);
		float s = sin(angle);
		float c = cos(angle);
		float oc = 1.0 - c;

		return glm::mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s, 0.0,
			oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s, 0.0,
			oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c, 0.0,
			0.0, 0.0, 0.0, 1.0);
	}
}
