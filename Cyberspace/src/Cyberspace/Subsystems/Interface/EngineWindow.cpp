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
		SetCursor(m_Props.Cursor);
	}

	void EngineWindow::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY)
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		glfwGetCursorPos(m_Window, &_CursorPosX, &_CursorPosY);
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			_BlockingEventQueue.push(new CyberEvent(EventType::EXIT));
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
		
		//if (!_EventQueue.empty()) {
		//	std::vector<EventTag>::iterator Tag = std::find(_EventQueue.front()->Tags.begin(), _EventQueue.front()->Tags.end(), EventTag::WINDOW);
		//	if (Tag != _EventQueue.front()->Tags.end()) {
		//		_EventQueue.front()->Tags.erase(Tag);
		//		switch (_EventQueue.front()->Type) {
		//		case EventType::TOGGLE_CAMERA_MOVEMENT:
		//			m_ShowCursor = !m_ShowCursor;
		//			m_ShowCursor ? 
		//				glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL) : 
		//				glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//			if (_EventQueue.front()->Tags.empty()) {
		//				_EventQueue.pop();
		//			}
		//			break;
		//		}
		//	}
		//}
	}

	GLFWwindow* EngineWindow::GetWindow()
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
