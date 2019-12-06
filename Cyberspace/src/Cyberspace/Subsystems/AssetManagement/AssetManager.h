#pragma once

#include "Model.h"
#include "Shader.h"
#include "../../../EngineProps.h"

namespace Cyberspace {

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


