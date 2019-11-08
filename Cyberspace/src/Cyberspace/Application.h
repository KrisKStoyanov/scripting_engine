#pragma once
#include "Core.h"

namespace Cyberspace {
	class CSPACE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run(); 
	};	

	//Defined in client app:
	Application* CreateApplication();
}


