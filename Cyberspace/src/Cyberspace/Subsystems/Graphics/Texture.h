#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../stb_image.h"
#include "../../Core.h"

namespace Cyberspace {
	enum class TextureType {
		DIFFUSE = 0,
		SPECULAR = 1,
		NORMAL = 2,
		HEIGHT = 3
	};

	GLuint TextureFromFile(const char* _Path);

	class CSPACE_API Texture {
	public:
		Texture(const char* _Path, TextureType _Type);
		Texture(const char* _Path, std::string _Directory, TextureType _Type);
		~Texture();
		GLuint ID;
		TextureType Type;
		std::string Path;
	};
}
