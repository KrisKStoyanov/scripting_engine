#include "Application.h"

namespace Cyberspace {

	Application::Application() {

		lua_State* engineSettingsParser = luaL_newstate();
		luaL_dofile(engineSettingsParser, "../resources/Scripts/EngineProps.lua");
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

		//Convert scripted data into engine format settings
		EngineProps EProps;
		EProps.m_GraphicsProps.m_WinTitle = gfxWinTitle.cast<std::string>();
		EProps.m_GraphicsProps.m_ResX = gfxResX.cast<int>();
		EProps.m_GraphicsProps.m_ResY = gfxResY.cast<int>();
		EProps.m_GraphicsProps.m_Fullscreen = gfxFullscreen.cast<bool>();
		EProps.m_GraphicsProps.m_BrdrlessFull = gfxBrdrless.cast<bool>();
		EProps.m_GraphicsProps.m_FOV = gfxFov.cast<float>();
		EProps.m_GraphicsProps.m_EnCursor = gfxEnCursor.cast<bool>();
		EProps.m_GraphicsProps.m_VSync = gfxVsync.cast<bool>();
		EProps.m_GraphicsProps.m_MSAA = gfxMsaa.cast<bool>();

		EProps.m_AMProps.VehicleModelPath = amVehicleModelPath.cast<std::string>();
		EProps.m_AMProps.ModelVertexShaderPath = amModelVertexShaderPath.cast<std::string>();
		EProps.m_AMProps.ModelFragmentShaderPath = amModelFragmentShaderPath.cast<std::string>();
		EProps.m_AMProps.SkyboxVertexShaderPath = amSkyboxVertexShaderPath.cast<std::string>();
		EProps.m_AMProps.SkyboxFragmentShaderPath = amSkyboxFragmentShaderPath.cast<std::string>();

		EProps.m_AudioProps.TitleScreenBGMFilePath = audioTitleScreenBgmFilePath.cast<const char*>();

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