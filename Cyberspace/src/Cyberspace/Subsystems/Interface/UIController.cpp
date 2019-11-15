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

		CreateWindow(_props.windowProps);
	}

	void UIController::CreateWindow(const WindowProps& _props, bool _setFocus)
	{
		AvailableWindows[_props.Title] = new EngineWindow(_props);
		if (_setFocus) {
			FocusedWindow = _props.Title;
			SetGraphicsContext(AvailableWindows[_props.Title]);
		}
	}

	void UIController::DeleteWindow(std::string _tag)
	{
		AvailableWindows.erase(_tag);
	}

	void UIController::SetGraphicsContext(EngineWindow* _window)
	{
		glfwMakeContextCurrent(_window->GetNativeWindow());
	}

	void UIController::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		AvailableWindows[FocusedWindow]->OnUpdate(_BlockingEventQueue, _EventQueue, CursorPosX, CursorPosY);
	}

	void UIController::Terminate()
	{
		for (auto it : AvailableWindows) {
			delete it.second;
		}

		glfwTerminate();
	}
}

