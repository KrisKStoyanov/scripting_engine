#include "EngineWindow.h"

namespace Cyberspace {
	EngineWindow* EngineWindow::Create(const GraphicsProps& _props)
	{
		return new EngineWindow(_props);
	}
	EngineWindow::EngineWindow(const GraphicsProps& _props)
	{
		Init(_props);
	}

	EngineWindow::~EngineWindow()
	{
		Terminate();
	}

	void EngineWindow::Init(const GraphicsProps& _props)
	{
		if (!glfwInit()) {
			printf("GLFW failed to initialize");
		}
		glfwSetErrorCallback([](int _Error, const char* _Description) {
			fprintf(stderr, "GLFW Error %d: %s\n", _Error, _Description);
			});

		//Pre-window creation settings:
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		if (_props.m_MSAA) {
			glfwWindowHint(GLFW_SAMPLES, 4);
			glEnable(GL_MULTISAMPLE);
		}

		m_Window = glfwCreateWindow(
			_props.m_DisFormat.ResX, 
			_props.m_DisFormat.ResY, 
			_props.m_WinTitle.c_str(), 
			_props.m_Fullscreen ? glfwGetPrimaryMonitor() : NULL, 
			NULL);
		glfwMakeContextCurrent(m_Window);

		if (_props.m_VSync) {
			glfwSwapInterval(1);
		} 
		else {
			glfwSwapInterval(0);
		}
		if (_props.m_EnCursor) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				
		}
		else {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	void EngineWindow::Recreate(const GraphicsProps& _props)
	{
		if (_props.m_MSAA) {
			glfwWindowHint(GLFW_SAMPLES, 4);
			glEnable(GL_MULTISAMPLE);
		}

		glfwSetWindowMonitor(m_Window, NULL, 0, 0, _props.m_DisFormat.ResX, _props.m_DisFormat.ResY, 0);

		GLFWwindow* bufferWindow = glfwCreateWindow(
			_props.m_DisFormat.ResX, 
			_props.m_DisFormat.ResY,
			_props.m_WinTitle.c_str(),
			_props.m_Fullscreen ? glfwGetPrimaryMonitor() : NULL,
			m_Window);

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

	void EngineWindow::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		glfwGetCursorPos(m_Window, &CursorPosX, &CursorPosY);
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(m_Window)) {
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

	void EngineWindow::Terminate()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}
