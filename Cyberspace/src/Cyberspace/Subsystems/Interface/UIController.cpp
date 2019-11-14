#include "UIController.h"

namespace Cyberspace {
	UIController* UIController::Create(const UIProps& _props)
	{
		return new UIController(_props);
	}
	Cyberspace::UIController::UIController(const UIProps& _props)
	{
		Init(_props);
	}

	Cyberspace::UIController::~UIController()
	{
		Terminate();
	}

	void UIController::Init(const UIProps& _props)
	{
		if (!glfwInit()) {
			printf("GLFW Window failed to initialize");
		}
		glfwSetErrorCallback([](int _Error, const char* _Description) {
			fprintf(stderr, "GLFW Error %d: %s\n", _Error, _Description);
			});

		AvailableWindows[FocusedWindow] = new EngineWindow(_props.PrimaryWindowProps);
		glfwMakeContextCurrent(AvailableWindows[FocusedWindow]->m_Window);
	}

	void UIController::SetGraphicsContext(EngineWindow* _window)
	{
		m_GUIToolkit->Configure(_window);
	}

	void UIController::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		AvailableWindows[FocusedWindow]->OnUpdate(_BlockingEventQueue, _EventQueue, CursorPosX, CursorPosY);
	}

	void UIController::OnUpdateGUI(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		m_GUIToolkit->OnUpdate(_BlockingEventQueue, _EventQueue);
	}

	void UIController::Terminate()
	{
		for (auto it : AvailableWindows) {
			delete it.second;
		}
		m_GUIToolkit.reset();
		glfwTerminate();
	}
}

