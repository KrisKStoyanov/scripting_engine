#include "Application.h"

namespace Cyberspace {

	Application::Application() {

		lua_State* engineSettingsParser = luaL_newstate();
		luaL_dofile(engineSettingsParser, "../../External Resources/Scripts/EngineProps.lua");
		luaL_openlibs(engineSettingsParser);
		lua_pcall(engineSettingsParser, 0, 0, 0);

		//Parse scripted data through lua
		luabridge::LuaRef winProps = luabridge::getGlobal(engineSettingsParser, "sadas");
		luabridge::LuaRef winTitle = winProps["title"];
		luabridge::LuaRef winWidth = winProps["width"];
		luabridge::LuaRef winHeight = winProps["height"];
		luabridge::LuaRef winVSync = winProps["vsync"];

		//Cast data through to c++ native format
		std::string winPropsTitle = winTitle.cast<std::string>();
		int winPropsWidth = winWidth.cast<int>();
		int winPropsHeight = winHeight.cast<int>();
		int winPropsVSync = winVSync.cast<bool>();

		luabridge::LuaRef gfxProps = luabridge::getGlobal(engineSettingsParser, "graphics");
		luabridge::LuaRef gfxWidth = gfxProps["width"];
		luabridge::LuaRef gfxHeight = gfxProps["height"];

		int gfxPropsWidth = gfxWidth.cast<int>();
		int gfxPropsHeight = gfxHeight.cast<int>();

		luabridge::LuaRef amProps = luabridge::getGlobal(engineSettingsParser, "assetManagement");
		luabridge::LuaRef amVehicleModelPath = amProps["vehicleModelPath"];
		luabridge::LuaRef amModelVertexShaderPath = amProps["modelVertexShaderPath"];
		luabridge::LuaRef amModelFragmentShaderPath = amProps["modelFragmentShaderPath"];
		luabridge::LuaRef amSkyboxVertexShaderPath = amProps["skyboxVertexShaderPath"];
		luabridge::LuaRef amSkyboxFragmentShaderPath = amProps["skyboxFragmentShaderPath"];

		std::string amPropsVehicleModelPath = amVehicleModelPath.cast<std::string>();
		std::string amPropsModelVertexShaderPath = amModelVertexShaderPath.cast<std::string>();
		std::string amPropsModelFragmentShaderPath = amModelFragmentShaderPath.cast<std::string>();
		std::string amPropsSkyboxVertexShaderPath = amSkyboxVertexShaderPath.cast<std::string>();
		std::string amPropsSkyboxFragmentShaderPath = amSkyboxFragmentShaderPath.cast<std::string>();

		//Create engine settings formatting struct
		EngineProps EProps;

		EProps.m_WindowProps.Title = winPropsTitle;
		EProps.m_WindowProps.Width = winPropsWidth;
		EProps.m_WindowProps.Height = winPropsHeight;
		EProps.m_WindowProps.VSyncStatus = winPropsVSync;

		EProps.m_GraphicsProps.Width = gfxPropsWidth;
		EProps.m_GraphicsProps.Height = gfxPropsHeight;

		EProps.m_AMProps.VehicleModelPath = amPropsVehicleModelPath;
		EProps.m_AMProps.ModelVertexShaderPath = amPropsModelVertexShaderPath;
		EProps.m_AMProps.ModelFragmentShaderPath = amPropsModelFragmentShaderPath;
		EProps.m_AMProps.SkyboxVertexShaderPath = amPropsSkyboxVertexShaderPath;
		EProps.m_AMProps.SkyboxFragmentShaderPath = amPropsSkyboxFragmentShaderPath;

		m_Engine = std::unique_ptr<CyberEngine>(CyberEngine::Create(EProps));
	}

	Application::~Application() {

	}
	void Application::Run()
	{
		m_Engine->Configure();
		while (m_Engine->m_Running)
		{
			m_Engine->OnUpdate();
		}
	}
}