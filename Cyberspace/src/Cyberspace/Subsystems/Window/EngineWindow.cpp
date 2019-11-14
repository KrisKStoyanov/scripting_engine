#include "EngineWindow.h"

namespace Cyberspace {
	EngineWindow* EngineWindow::Create(const WindowProps& _props)
	{
		return new EngineWindow(_props);
	}

	EngineWindow::EngineWindow(const WindowProps& _props)
	{
		InitWindow(_props);
	}

	EngineWindow::~EngineWindow()
	{
		Terminate();
	}

	void EngineWindow::InitWindow(const WindowProps& _props)
	{
		if (!glfwInit()) {
			printf("GLFW Window failed to initialize");
		}

		MainWindow = glfwCreateWindow(_props.Width, _props.Height, _props.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(MainWindow);

		SetVSync(_props.VSyncStatus);

		glfwSetErrorCallback([](int _Error, const char* _Description) {
			fprintf(stderr, "GLFW Error %d: %s\n", _Error, _Description);
			});

		m_WindowWidth = _props.Width;
		m_WindowHeight = _props.Height;
		m_VSync = _props.VSyncStatus;

		if (m_ShowCursor) {
			glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		
	}

	void EngineWindow::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY)
	{
		glfwSwapBuffers(MainWindow);
		glfwPollEvents();

		glfwGetCursorPos(MainWindow, &_CursorPosX, &_CursorPosY);
		//Blocking event:
		if (glfwGetKey(MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			_BlockingEventQueue.push(new CyberEvent(EventType::EXIT));
		}

		//Non-blocking event:
		if (glfwGetKey(MainWindow, GLFW_KEY_UP) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::CAMERA_MOVE_FORWARD, EventTag::GRAPHICS));
		}
		if (glfwGetKey(MainWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::CAMERA_MOVE_BACKWARD, EventTag::GRAPHICS));
		}
		if (glfwGetKey(MainWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::CAMERA_MOVE_LEFT, EventTag::GRAPHICS));
		}
		if (glfwGetKey(MainWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::CAMERA_MOVE_RIGHT, EventTag::GRAPHICS));
		}

		//if (glfwGetKey(MainWindow, GLFW_KEY_W) == GLFW_PRESS) {
		//	_EventQueue.push(new CyberEvent(EventType::VEHICLE_MOVE_FORWARD, EventTag::GRAPHICS));
		//}
		//if (glfwGetKey(MainWindow, GLFW_KEY_S) == GLFW_PRESS) {
		//	_EventQueue.push(new CyberEvent(EventType::VEHICLE_MOVE_BACKWARD, EventTag::GRAPHICS));
		//}
		//if (glfwGetKey(MainWindow, GLFW_KEY_A) == GLFW_PRESS) {
		//	_EventQueue.push(new CyberEvent(EventType::VEHICLE_MOVE_LEFT, EventTag::GRAPHICS));
		//}
		//if (glfwGetKey(MainWindow, GLFW_KEY_D) == GLFW_PRESS) {
		//	_EventQueue.push(new CyberEvent(EventType::VEHICLE_MOVE_RIGHT, EventTag::GRAPHICS));
		//}
	}

	void EngineWindow::Terminate()
	{
		glfwDestroyWindow(MainWindow);
		glfwTerminate();
	}
}
