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
		if (!glfwInit()) {
			printf("GLFW Window failed to initialize");
		}

		MainWindow = glfwCreateWindow(_props.Width, _props.Height, _props.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(MainWindow);

		SetVSync(true);

		glfwSetErrorCallback([](int _Error, const char* _Description) {
			fprintf(stderr, "GLFW Error %d: %s\n", _Error, _Description);
			});

		glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//glfwSetKeyCallback(PlatformWindow, [](GLFWwindow* _Window, int _Key, int _Scancode, int _Action, int _Mods) {
		//	if (_Key == GLFW_KEY_ESCAPE && _Action == GLFW_PRESS) {
		//		
		//	}
		//	});
	}

	void EngineWindow::SetVSync(bool _Status)
	{
		_Status ? glfwSwapInterval(1) : glfwSwapInterval(0);
		VSyncStatus = _Status;
	}

	bool EngineWindow::GetVSync()
	{
		return VSyncStatus;
	}

	void EngineWindow::Update(std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY)
	{
		glfwSwapBuffers(MainWindow);
		glfwPollEvents();

		glfwGetCursorPos(MainWindow, &_CursorPosX, &_CursorPosY);
		if (glfwGetKey(MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::EXIT));
		}
		if (glfwGetKey(MainWindow, GLFW_KEY_W) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::MOVE_FORWARD, EventTag::GRAPHICS, EventTag::PHYSICS));
		}
		if (glfwGetKey(MainWindow, GLFW_KEY_S) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::MOVE_BACKWARD, EventTag::GRAPHICS, EventTag::PHYSICS));
		}
		if (glfwGetKey(MainWindow, GLFW_KEY_A) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::MOVE_LEFT, EventTag::GRAPHICS, EventTag::PHYSICS));
		}
		if (glfwGetKey(MainWindow, GLFW_KEY_D) == GLFW_PRESS) {
			_EventQueue.push(new CyberEvent(EventType::MOVE_RIGHT, EventTag::GRAPHICS, EventTag::PHYSICS));
		}
	}

	void EngineWindow::Terminate()
	{
		glfwDestroyWindow(MainWindow);
		glfwTerminate();
	}
}
