#include "Application.h"

namespace Cyberspace {

	Application::Application() {
		
		//Convert scripted data into engine format settings
		EngineProps EProps = Cyberspace::Script::ParseEngineProps("../resources/Scripts/EngineProps.lua");

		EProps.m_GraphicsProps.m_AvDisFormats = 
			Cyberspace::Script::ParseDisplayFormatList("ResFormatList", "../resources/Scripts/EngineProps.lua");


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