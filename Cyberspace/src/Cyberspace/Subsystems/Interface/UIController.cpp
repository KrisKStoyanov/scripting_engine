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
		SetVSync(_props.VSync);
		SetCursor(_props.Cursor);
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

	void UIController::SetVSync(bool _enable)
	{
		m_VSync = _enable;
		m_VSync ? glfwSwapInterval(1) : glfwSwapInterval(0);
	}

	void UIController::SetCursor(bool _enable)
	{
		m_Cursor = _enable;
		m_Cursor ?
			glfwSetInputMode(AvailableWindows[FocusedWindow]->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL) :
			glfwSetInputMode(AvailableWindows[FocusedWindow]->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void UIController::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		AvailableWindows[FocusedWindow]->OnUpdate(_BlockingEventQueue, _EventQueue, CursorPosX, CursorPosY);

		if (!_BlockingEventQueue.empty()) {
			std::vector<EventTag>::iterator Tag = std::find(_BlockingEventQueue.front()->Tags.begin(), _BlockingEventQueue.front()->Tags.end(), EventTag::WINDOW);
			if (Tag != _BlockingEventQueue.front()->Tags.end()) {
				_BlockingEventQueue.front()->Tags.erase(Tag);
				switch (_BlockingEventQueue.front()->Type) {

				case EventType::TOGGLE_CURSOR:
					m_Cursor = !m_Cursor;
					SetCursor(m_Cursor);
					if (_BlockingEventQueue.front()->Tags.empty()) {
						_BlockingEventQueue.pop();
					}
					break;
				}
			}
		}
	}

	void UIController::Terminate()
	{
		for (auto it : AvailableWindows) {
			delete it.second;
		}

		glfwTerminate();
	}
}

