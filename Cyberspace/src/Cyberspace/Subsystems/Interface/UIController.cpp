#include "UIController.h"

namespace Cyberspace {
	UIController* UIController::Create(const WindowProps& _props)
	{
		return new UIController(_props);
	}
	Cyberspace::UIController::UIController(const WindowProps& _props)
	{
		Init(_props);
	}

	Cyberspace::UIController::~UIController()
	{
		Terminate();
	}

	void UIController::Init(const WindowProps& _props)
	{
		if (!glfwInit()) {
			printf("GLFW Window failed to initialize");
		}
		glfwSetErrorCallback([](int _Error, const char* _Description) {
			fprintf(stderr, "GLFW Error %d: %s\n", _Error, _Description);
			});

		m_Window = new EngineWindow(_props);
		glfwMakeContextCurrent(m_Window->GetNativeWindow());
		m_Window->SetVSync(_props.VSync);
	}

	void UIController::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		m_Window->OnUpdate(_BlockingEventQueue, _EventQueue, CursorPosX, CursorPosY);
	}

	void UIController::Terminate()
	{
		glfwTerminate();
	}
}

