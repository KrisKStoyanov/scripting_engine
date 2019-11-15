#include "EngineWindow.h"

namespace Cyberspace {
	EngineWindow::EngineWindow(const WindowProps& _props)
	{
		Configure(_props);
	}

	EngineWindow::~EngineWindow()
	{
		Terminate();
	}

	void EngineWindow::Configure(const WindowProps& _props)
	{
		m_Props = _props;
		m_Window = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title.c_str(), NULL, NULL);
		SetCursorEnabled(_props.CursorEnabled);
	}

	void EngineWindow::SetCursorEnabled(bool _enable)
	{
		m_Cursor = _enable;
		m_Cursor ?
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL) :
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void EngineWindow::SetVSync(bool _enable)
	{
		m_VSync = _enable;
		m_VSync ? glfwSwapInterval(1) : glfwSwapInterval(0);
	}

	void EngineWindow::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY)
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		glfwGetCursorPos(m_Window, &_CursorPosX, &_CursorPosY);
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			_BlockingEventQueue.push(new CyberEvent(EventType::EXIT));
		}
		if (glfwGetKey(m_Window, GLFW_KEY_G) == GLFW_PRESS) {
			_BlockingEventQueue.push(new CyberEvent(EventType::TOGGLE_GUI, EventTag::GRAPHICS));
		}
		if (glfwGetKey(m_Window, GLFW_KEY_C) == GLFW_PRESS) {
			_BlockingEventQueue.push(new CyberEvent(EventType::TOGGLE_CURSOR, EventTag::WINDOW));
		}

		if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::CAMERA_MOVE_FORWARD, EventTag::GRAPHICS));
		}
		if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::CAMERA_MOVE_BACKWARD, EventTag::GRAPHICS));
		}
		if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::CAMERA_MOVE_LEFT, EventTag::GRAPHICS));
		}
		if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::CAMERA_MOVE_RIGHT, EventTag::GRAPHICS));
		}

		if (!_BlockingEventQueue.empty()) {
			std::vector<EventTag>::iterator Tag = std::find(_BlockingEventQueue.front()->Tags.begin(), _BlockingEventQueue.front()->Tags.end(), EventTag::WINDOW);
			if (Tag != _BlockingEventQueue.front()->Tags.end()) {
				_BlockingEventQueue.front()->Tags.erase(Tag);
				switch (_BlockingEventQueue.front()->Type) {

				case EventType::TOGGLE_CURSOR:
					m_Cursor = !m_Cursor;
					SetCursorEnabled(m_Cursor);
					if (_BlockingEventQueue.front()->Tags.empty()) {
						_BlockingEventQueue.pop();
					}
					break;
				}
			}
		}
	
	}

	GLFWwindow* EngineWindow::GetNativeWindow()
	{
		return m_Window; 
	}

	WindowProps EngineWindow::GetWindowProps()
	{
		return m_Props;
	}

	void EngineWindow::Terminate()
	{
		glfwDestroyWindow(m_Window);
	}
}
