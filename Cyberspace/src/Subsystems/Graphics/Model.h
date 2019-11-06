#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "Mesh.h"
#include "Texture.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../../stb_image.h"

GLint TextureFromFile(const char* _Path, std::string _Directory);

class Model
{
public:
	Model(std::string const _Path);
	~Model();
	std::vector<Mesh> Meshes;
	std::string Directory;
	std::vector<Texture> LoadedTextures;

	void LoadModel(std::string const &_Path);
	void ProcessNode(aiNode* _Node, const aiScene* _Scene);
	Mesh ProcessMesh(aiMesh* _Mesh, const aiScene* _Scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* _Material, aiTextureType _Type, TextureType _TypeName);

	glm::mat4 ModelMatrix = glm::mat4(1.0f);
};

