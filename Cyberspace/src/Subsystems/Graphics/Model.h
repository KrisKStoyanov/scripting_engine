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
	Model(char* _Path){
		LoadModel(_Path);
	}
private:
	std::vector<Mesh> Meshes;
	std::string Directory;
	void LoadModel(std::string _Path);
	void ProcessNode(aiNode* _Node, const aiScene* _Scene);
	Mesh ProcessMesh(aiMesh* _Mesh, const aiScene* _Scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* _Material, aiTextureType _Type, std::string _TypeName);
	std::vector<Texture> textures_loaded;
};

