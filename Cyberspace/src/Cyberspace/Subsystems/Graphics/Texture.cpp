#include "cspacepch.h"
#include "Texture.h"

namespace Cyberspace {
	Texture::Texture(const char* _Path, TextureType _Type)
	{
		Path = _Path;
		Type = _Type;
		ID = TextureFromFile(_Path);
	}

	Texture::Texture(const char* _Path, std::string _Directory, TextureType _Type)
	{
		Path = _Path;
		Type = _Type;
		std::string filename = std::string(_Path);
		filename = _Directory + '/' + filename;
		ID = TextureFromFile(filename.c_str());
	}

	Texture::~Texture()
	{
	}

	GLuint TextureFromFile(const char* _Path)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(_Path, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format = GL_RGBA;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			printf("Texture failed to load at path: %s\n", _Path);
			stbi_image_free(data);
		}

		return textureID;
	}
}
