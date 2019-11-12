#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "../../Core.h"
#include "Model.h"
#include "Shader.h"

namespace Cyberspace {

	struct AMProps {
		std::string VehicleModelPath;
		std::string ModelVertexShaderPath, ModelFragmentShaderPath;
		std::string SkyboxVertexShaderPath, SkyboxFragmentShaderPath;
		AMProps(
			std::string _VehicleModelPath = "../External Resources/3D/Vehicle/SpaceCarEngine.fbx",
			std::string _ModelVertexShaderPath = "/Shaders/TextureVertexShader.glsl",
			std::string _ModelFragmentShaderPath = "/Shaders/TextureFragmentShader.glsl",
			std::string _SkyboxVertexShaderPath = "/Shaders/SkyboxVertexShader.glsl",
			std::string _SkyboxFragmentShaderPath = "/Shaders/SkyboxFragmentShader.glsl") :
			VehicleModelPath(_VehicleModelPath), 
			ModelVertexShaderPath(_ModelVertexShaderPath), ModelFragmentShaderPath(_ModelFragmentShaderPath),
			SkyboxVertexShaderPath(_SkyboxVertexShaderPath), SkyboxFragmentShaderPath(_SkyboxFragmentShaderPath)
		{}
	};

	class CSPACE_API AssetManager
	{
	public:
		static AssetManager* Create(const AMProps& _props = AMProps());
		AssetManager(const AMProps& _props);
		~AssetManager();
		void Init(const AMProps& _props);
		void Terminate();
		std::unordered_map<std::string, Model*> LoadedModels;
		std::unordered_map<std::string, Shader*> LoadedShaders;
	};
}


