#include "AssetManager.h"

namespace Cyberspace {
	AssetManager* Cyberspace::AssetManager::Create(const AMProps& _props)
	{
		return new AssetManager(_props);
	}

	Cyberspace::AssetManager::AssetManager(const AMProps& _props)
	{
		Init(_props);
	}

	Cyberspace::AssetManager::~AssetManager()
	{
		Terminate();
	}

	void Cyberspace::AssetManager::Init(const AMProps& _props)
	{
		//LoadedModels["Nanosuit"] = new Model("../External Resources/3D/crysisGuy/scene.gltf");
		//LoadedModels["Cruiser"] = new Model("../External Resources/3D/Vehicle/SpaceCar.fbx");
		LoadedModels["Vehicle"] = new Model("../External Resources/3D/Vehicle/SpaceCarEngine.fbx");
		LoadedShaders["Texture"] = new Shader("/Shaders/TextureVertexShader.glsl", "/Shaders/TextureFragmentShader.glsl");
		LoadedShaders["Skybox"] = new Shader("/Shaders/SkyboxVertexShader.glsl", "/Shaders/SkyboxFragmentShader.glsl");
	}

	void Cyberspace::AssetManager::Terminate()
	{
		for (auto it : LoadedModels) {
			delete it.second;
		}
	}
}
