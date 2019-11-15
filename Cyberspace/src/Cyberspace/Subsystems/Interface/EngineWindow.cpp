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
