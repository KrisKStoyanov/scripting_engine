#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Core.h"

namespace Cyberspace {
	class CSPACE_API Material
	{
		Material();
		~Material();
		glm::vec3 AmbientC;
		glm::vec3 DiffuseC;
		glm::vec3 SpecularC;
		float Shininess;
	};
}


