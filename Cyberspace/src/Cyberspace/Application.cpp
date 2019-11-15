#include "Application.h"

namespace Cyberspace {

	Application::Application() {

		lua_State* engineSettingsParser = luaL_newstate();
		luaL_dofile(engineSettingsParser, "../resources/Scripts/EngineProps.lua");
		luaL_openlibs(engineSettingsParser);
		lua_pcall(engineSettingsParser, 0, 0, 0);

		//Parse scripted data through lua
		luabridge::LuaRef winProps = luabridge::getGlobal(engineSettingsParser, "window");
		luabridge::LuaRef winTitle = winProps["title"];
		luabridge::LuaRef winWidth = winProps["width"];
		luabridge::LuaRef winHeight = winProps["height"];
		luabridge::LuaRef winVSync = winProps["vsync"];

		luabridge::LuaRef gfxProps = luabridge::getGlobal(engineSettingsParser, "graphics");
		luabridge::LuaRef gfxWidth = gfxProps["cameraWidth"];
		luabridge::LuaRef gfxHeight = gfxProps["cameraHeight"];
		luabridge::LuaRef gfxFOV = gfxProps["cameraFOV"];
		luabridge::LuaRef gfxSkyboxFaceTexturePaths = gfxProps["skyboxFaceTexturePaths"];

		luabridge::LuaRef amProps = luabridge::getGlobal(engineSettingsParser, "assetManagement");
		luabridge::LuaRef amVehicleModelPath = amProps["vehicleModelPath"];
		luabridge::LuaRef amModelVertexShaderPath = amProps["modelVertexShaderPath"];
		luabridge::LuaRef amModelFragmentShaderPath = amProps["modelFragmentShaderPath"];
		luabridge::LuaRef amSkyboxVertexShaderPath = amProps["skyboxVertexShaderPath"];
		luabridge::LuaRef amSkyboxFragmentShaderPath = amProps["skyboxFragmentShaderPath"];

		luabridge::LuaRef audioProps = luabridge::getGlobal(engineSettingsParser, "audio");
		luabridge::LuaRef audioTitleScreenBgmFilePath = audioProps["titleScreenBgmFilePath"];

		//Cast data through to c++ native format
		std::string winPropsTitle = winTitle.cast<std::string>();
		int winPropsWidth = winWidth.cast<int>();
		int winPropsHeight = winHeight.cast<int>();
		int winPropsVSync = winVSync.cast<bool>();

		int gfxPropsWidth = gfxWidth.cast<int>();
		int gfxPropsHeight = gfxHeight.cast<int>();
		int gfxPropsFOV = gfxFOV.cast<float>();

		std::string amPropsVehicleModelPath = amVehicleModelPath.cast<std::string>();
		std::string amPropsModelVertexShaderPath = amModelVertexShaderPath.cast<std::string>();
		std::string amPropsModelFragmentShaderPath = amModelFragmentShaderPath.cast<std::string>();
		std::string amPropsSkyboxVertexShaderPath = amSkyboxVertexShaderPath.cast<std::string>();
		std::string amPropsSkyboxFragmentShaderPath = amSkyboxFragmentShaderPath.cast<std::string>();

		const char* audioPropsTitleScreenBgmFilePath = audioTitleScreenBgmFilePath.cast<const char*>();

		//Create engine settings formatting struct
		EngineProps EProps;

		WindowProps WProps;
		WProps.Title = winPropsTitle;
		WProps.Width = winPropsWidth;
		WProps.Height = winPropsHeight;
		EProps.m_UIProps.VSync = winPropsVSync;
		EProps.m_UIProps.Cursor = true;

		EProps.m_UIProps.windowProps = WProps;

		EProps.m_GraphicsProps.Width = gfxPropsWidth;
		EProps.m_GraphicsProps.Height = gfxPropsHeight;
		EProps.m_GraphicsProps.FOV = gfxPropsFOV;

		EProps.m_AMProps.VehicleModelPath = amPropsVehicleModelPath;
		EProps.m_AMProps.ModelVertexShaderPath = amPropsModelVertexShaderPath;
		EProps.m_AMProps.ModelFragmentShaderPath = amPropsModelFragmentShaderPath;
		EProps.m_AMProps.SkyboxVertexShaderPath = amPropsSkyboxVertexShaderPath;
		EProps.m_AMProps.SkyboxFragmentShaderPath = amPropsSkyboxFragmentShaderPath;

		EProps.m_AudioProps.TitleScreenBGMFilePath = audioPropsTitleScreenBgmFilePath;

		m_Engine = std::unique_ptr<CyberEngine>(CyberEngine::Create(EProps));
	}

	Application::~Application() {
		m_Engine.reset();
	}
	void Application::Run()
	{
		while (m_Engine->GetTick())
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_Engine->OnUpdate(timestep);
			
		}
	}
}