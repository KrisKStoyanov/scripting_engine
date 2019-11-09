#include "Application.h"

namespace Cyberspace {

	Application::Application() {
		m_Engine = std::unique_ptr<CyberEngine>(CyberEngine::Create());
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
		m_Engine->Terminate();
	}
}