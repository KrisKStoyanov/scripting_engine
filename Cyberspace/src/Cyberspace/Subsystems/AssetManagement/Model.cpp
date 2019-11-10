#include "Model.h"

namespace Cyberspace {
	Model::Model(std::string const _Path) {
		LoadModel(_Path);
	}

	Model::~Model()
	{
	}

	void Model::LoadModel(std::string const& _Path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(_Path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
		Directory = _Path.substr(0, _Path.find_last_of('/'));
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* _Node, const aiScene* _Scene)
	{
		for (unsigned int i = 0; i < _Node->mNumMeshes; ++i) {
			aiMesh* Mesh = _Scene->mMeshes[_Node->mMeshes[i]];
			Meshes.push_back(ProcessMesh(Mesh, _Scene));
		}

		for (unsigned int i = 0; i < _Node->mNumChildren; ++i) {
			ProcessNode(_Node->mChildren[i], _Scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* _Mesh, const aiScene* _Scene)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < _Mesh->mNumVertices; ++i) {
			Vertex vertex;
			glm::vec3 vertexData;
			//Position data parsing
			vertexData.x = _Mesh->mVertices[i].x;
			vertexData.y = _Mesh->mVertices[i].y;
			vertexData.z = _Mesh->mVertices[i].z;
			vertex.Position = vertexData;
			//Normal data parsing
			vertexData.x = _Mesh->mNormals[i].x;
			vertexData.y = _Mesh->mNormals[i].y;
			vertexData.z = _Mesh->mNormals[i].z;
			vertex.Normal = vertexData;
			if (_Mesh->mTextureCoords[0]) {
				glm::vec2 textureData;
				textureData.x = _Mesh->mTextureCoords[0][i].x;
				textureData.y = _Mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = textureData;
			}
			else {
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < _Mesh->mNumFaces; ++i) {
			aiFace face = _Mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j) {
				indices.push_back(face.mIndices[j]);
			}
		}

		if (_Mesh->mMaterialIndex >= 0) {
			aiMaterial* material = _Scene->mMaterials[_Mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, TextureType::NORMAL);
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::HEIGHT);
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		}
		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* _Material, aiTextureType _Type, TextureType _TypeName)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < _Material->GetTextureCount(_Type); ++i) {
			aiString str;
			_Material->GetTexture(_Type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < LoadedTextures.size(); ++j) {
				if (std::strcmp(LoadedTextures[j].Path.data(), str.C_Str()) == 0) {
					//textures.push_back(LoadedTextures[j]);
					skip = true;
					break;
				}
			}
			if (!skip) {
				Texture texture(str.C_Str(), Directory, _TypeName);
				textures.push_back(texture);
				LoadedTextures.push_back(texture);
			}
		}
		return textures;
	}
}

