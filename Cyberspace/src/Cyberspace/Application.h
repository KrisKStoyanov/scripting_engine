#pragma once
#include "Core.h"
#include "CyberEngine.h"

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
	};	

	//Defined in client app:
	Application* CreateApplication();
}


