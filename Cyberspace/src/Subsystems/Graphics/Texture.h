#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../stb_image.h"

enum class TextureType {
	DIFFUSE = 0,
	SPECULAR = 1,
	NORMAL = 2,
	HEIGHT = 3
};

struct Texture {
	GLuint id;
	TextureType type;
	std::string path;
};