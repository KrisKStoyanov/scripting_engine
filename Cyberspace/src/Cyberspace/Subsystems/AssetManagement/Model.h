#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Graphics/Vertex.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../../stb_image.h"
#include "../../Core.h"

namespace Cyberspace {
	class CSPACE_API Model
	{
	public:
		Model(std::string const _Path);
		Model(const Model& _other);
		~Model();
		std::vector<Mesh> Meshes;
		std::string Directory;
		std::vector<Texture> LoadedTextures;

		void LoadModel(std::string const& _Path);
		void ProcessNode(aiNode* _Node, const aiScene* _Scene);
		Mesh ProcessMesh(aiMesh* _Mesh, const aiScene* _Scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* _Material, aiTextureType _Type, TextureType _TypeName);
	};
}


