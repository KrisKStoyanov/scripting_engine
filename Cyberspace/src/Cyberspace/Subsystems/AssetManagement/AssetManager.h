#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "../../Core.h"
#include "../../Subsystems/Graphics/Model.h"

namespace Cyberspace {

	struct AMProps {
		AMProps() {}
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
	};
}


