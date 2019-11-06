#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
	Material();
	~Material();
	glm::vec3 AmbientC;
	glm::vec3 DiffuseC;
	glm::vec3 SpecularC;
	float Shininess;
};

