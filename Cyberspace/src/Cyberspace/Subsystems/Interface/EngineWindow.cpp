#include "EngineWindow.h"

namespace Cyberspace {
	EngineWindow* EngineWindow::Create(const WindowProps& _props)
	{
		return new EngineWindow(_props);
	}
	EngineWindow::EngineWindow(const WindowProps& _props)
	{
		Init(_props);
	}

	EngineWindow::~EngineWindow()
	{
		Terminate();
	}

	void EngineWindow::Init(const WindowProps& _props)
	{
		m_Props = _props;

		if (!glfwInit()) {
			printf("GLFW failed to initialize");
		}
		glfwSetErrorCallback([](int _Error, const char* _Description) {
			fprintf(stderr, "GLFW Error %d: %s\n", _Error, _Description);
			});

		m_Window = glfwCreateWindow(m_Props.Width, m_Props.Height, m_Props.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		SetVSync(m_Props.VSync);
		SetCursorEnabled(m_Props.CursorEnabled);
	}

	void EngineWindow::Recreate(const WindowProps& _props)
	{
		GLFWwindow* bufferWindow = glfwCreateWindow(_props.Width, _props.Height, _props.Title.c_str(), NULL, m_Window);
		glfwDestroyWindow(m_Window);
		m_Window = bufferWindow;
		glfwMakeContextCurrent(m_Window);

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
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

	void EngineWindow::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, double &_cursorPosX, double &_cursorPosY)
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		glfwGetCursorPos(m_Window, &_cursorPosX, &_cursorPosY);
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

				case EventType::TOGGLE_CAMERA_MOVEMENT:
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
