#pragma once
#include "../../Core.h"
#include "../../../EngineProps.h"
#include <string>
#include <vector>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"

namespace Cyberspace {
	class CSPACE_API Script
	{
	public:
		static EngineProps ParseEngineProps(const char* _scriptPath);
		static std::vector<ResDisplayFormat> ParseDisplayFormatList(const std::string& _tab, const char* _scriptPath);
		static std::vector<std::string> ParseElementList(const std::string& _tab, const char* _scriptPath);
	};
}

