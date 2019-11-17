#include "Script.h"

namespace Cyberspace {
	EngineProps Script::ParseEngineProps(const char* _scriptPath)
	{
		EngineProps props = EngineProps();
		lua_State* engineSettingsParser = luaL_newstate();
		luaL_dofile(engineSettingsParser, _scriptPath);
		luaL_openlibs(engineSettingsParser);
		lua_pcall(engineSettingsParser, 0, 0, 0);

		//Parse scripted data through lua
		luabridge::LuaRef gfxProps = luabridge::getGlobal(engineSettingsParser, "Graphics");
		luabridge::LuaRef gfxWinTitle = gfxProps["winTitle"];
		luabridge::LuaRef gfxResX = gfxProps["defaultResX"];
		luabridge::LuaRef gfxResY = gfxProps["defaultResY"];
		luabridge::LuaRef gfxFullscreen = gfxProps["fullscreen"];
		luabridge::LuaRef gfxBrdrless = gfxProps["borderlessFullscreen"];
		luabridge::LuaRef gfxFov = gfxProps["fov"];
		luabridge::LuaRef gfxEnCursor = gfxProps["enableCursor"];
		luabridge::LuaRef gfxVsync = gfxProps["vsync"];
		luabridge::LuaRef gfxMsaa = gfxProps["msaa"];

		luabridge::LuaRef amProps = luabridge::getGlobal(engineSettingsParser, "assetManagement");
		luabridge::LuaRef amVehicleModelPath = amProps["vehicleModelPath"];
		luabridge::LuaRef amModelVertexShaderPath = amProps["modelVertexShaderPath"];
		luabridge::LuaRef amModelFragmentShaderPath = amProps["modelFragmentShaderPath"];
		luabridge::LuaRef amSkyboxVertexShaderPath = amProps["skyboxVertexShaderPath"];
		luabridge::LuaRef amSkyboxFragmentShaderPath = amProps["skyboxFragmentShaderPath"];

		luabridge::LuaRef audioProps = luabridge::getGlobal(engineSettingsParser, "audio");
		luabridge::LuaRef audioTitleScreenBgmFilePath = audioProps["titleScreenBgmFilePath"];

		//Convert and set to engine format data 
		props.m_GraphicsProps.m_WinTitle = gfxWinTitle.cast<std::string>();
		props.m_GraphicsProps.m_DisFormat.ResX = gfxResX.cast<int>();
		props.m_GraphicsProps.m_DisFormat.ResY = gfxResY.cast<int>();
		props.m_GraphicsProps.m_Fullscreen = gfxFullscreen.cast<bool>();
		props.m_GraphicsProps.m_BrdrlessFull = gfxBrdrless.cast<bool>();
		props.m_GraphicsProps.m_FOV = gfxFov.cast<float>();
		props.m_GraphicsProps.m_EnCursor = gfxEnCursor.cast<bool>();
		props.m_GraphicsProps.m_VSync = gfxVsync.cast<bool>();
		props.m_GraphicsProps.m_MSAA = gfxMsaa.cast<bool>();

		props.m_AMProps.VehicleModelPath = amVehicleModelPath.cast<std::string>();
		props.m_AMProps.ModelVertexShaderPath = amModelVertexShaderPath.cast<std::string>();
		props.m_AMProps.ModelFragmentShaderPath = amModelFragmentShaderPath.cast<std::string>();
		props.m_AMProps.SkyboxVertexShaderPath = amSkyboxVertexShaderPath.cast<std::string>();
		props.m_AMProps.SkyboxFragmentShaderPath = amSkyboxFragmentShaderPath.cast<std::string>();

		props.m_AudioProps.TitleScreenBGMFilePath = audioTitleScreenBgmFilePath.cast<const char*>();

		return props;

	}
	std::vector<ResDisplayFormat> Script::ParseDisplayFormatList(const std::string& _tab, const char* _scriptPath)
	{
		lua_State* L = luaL_newstate();
		luaL_dofile(L, _scriptPath);
		luaL_openlibs(L);
		lua_pcall(L, 0, 0, 0);

		std::string source =
			"function ParseElementList(_tab) "
			"s = \"\""
			"for k, v in pairs(_G[_tab]) do "
			"    s = s..k..\"|\" "
			"    end "
			"return s "
			"end";

		luaL_loadstring(L, source.c_str());
		lua_pcall(L, 0, 0, 0);
		lua_getglobal(L, "ParseElementList");
		lua_pushstring(L, _tab.c_str());
		lua_pcall(L, 1, 1, 0);

		std::string ans = lua_tostring(L, -1);
		std::vector<std::string> elements;
		std::string temp = "";
		for (unsigned int i = 0; i < ans.size(); i++) {
			if (ans.at(i) != '|') {
				temp += ans.at(i);
			}
			else {
				elements.push_back(temp);
				temp = "";
			}
		}

		int n = lua_gettop(L);
		lua_pop(L, 1);

		std::vector<ResDisplayFormat> displayFormatList;
		luabridge::LuaRef elemListRef = luabridge::getGlobal(L, _tab.c_str());
		for (int i = 0; i < elements.size(); ++i) {
			luabridge::LuaRef elemRef = elemListRef[elements.at(i)];
			ResDisplayFormat disFormat;
			disFormat.ResX = elemRef["ResX"];
			disFormat.ResY = elemRef["ResY"];
			disFormat.DisplayFormat = std::to_string(disFormat.ResX) + "x" + std::to_string(disFormat.ResY);
			displayFormatList.push_back(disFormat);
		}
		return displayFormatList;
	}
	std::vector<std::string> Script::ParseElementList(const std::string& _tab, const char* _scriptPath)
	{
		lua_State* L = luaL_newstate();
		luaL_dofile(L, _scriptPath);
		luaL_openlibs(L);
		lua_pcall(L, 0, 0, 0);

		std::string source =
			"function ParseElementList(_tab) "
			"s = \"\""
			"for k, v in pairs(_G[_tab]) do "
			"    s = s..k..\"|\" "
			"    end "
			"return s "
			"end";

		luaL_loadstring(L, source.c_str());
		lua_pcall(L, 0, 0, 0);
		lua_getglobal(L, "ParseElementList");
		lua_pushstring(L, _tab.c_str());
		lua_pcall(L, 1, 1, 0);

		std::string ans = lua_tostring(L, -1);
		std::vector<std::string> elements;
		std::string temp = "";
		for (unsigned int i = 0; i < ans.size(); i++) {
			if (ans.at(i) != '|') {
				temp += ans.at(i);
			}
			else {
				elements.push_back(temp);
				temp = "";
			}
		}

		int n = lua_gettop(L);
		lua_pop(L, 1);

		return elements;
	}
}