#pragma once
#include "Core.h"
#include "CyberEngine.h"
#include "Core/Timestep.h"


namespace Cyberspace {
	class CSPACE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run(); 
	private:
		std::unique_ptr<CyberEngine> m_Engine; 
		bool m_Running = true;
		float m_LastFrameTime = 0.0f;
	};	

	//Defined in client app:
	Application* CreateApplication();
}


