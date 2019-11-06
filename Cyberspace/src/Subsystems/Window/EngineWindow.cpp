#include "EngineWindow.h"


EngineWindow::EngineWindow(bool& _InitStatus, const char* _Title, const unsigned int _Width, const unsigned int _Height)
{
	_InitStatus = Init(_Title, _Width, _Height);
}

EngineWindow::~EngineWindow()
{
}

bool EngineWindow::Init(const char* _Title, const unsigned int _Width, const unsigned int _Height)
{
	if (!glfwInit()) {
		return false;
	}

	MainWindow = glfwCreateWindow(_Width, _Height, _Title, NULL, NULL);
	if (!MainWindow) {
		glfwTerminate();
		return false;
	}
	Width = _Width;
	Height = _Height;
	glfwMakeContextCurrent(MainWindow);

	SetVsync(true);

	//Anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback([](int _Error, const char* _Description) {
		fprintf(stderr, "GLFW Error %d: %s\n", _Error, _Description);
		});

	glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetKeyCallback(PlatformWindow, [](GLFWwindow* _Window, int _Key, int _Scancode, int _Action, int _Mods) {
	//	if (_Key == GLFW_KEY_ESCAPE && _Action == GLFW_PRESS) {
	//		
	//	}
	//	});
	Active = true;

	return true;
}

void EngineWindow::SetVsync(bool _Status)
{
	_Status ? glfwSwapInterval(1) : glfwSwapInterval(0);
	VsyncStatus = _Status;
}

bool EngineWindow::GetVsyncStatus()
{
	return VsyncStatus;
}

void EngineWindow::Update(std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY)
{
	glfwSwapBuffers(MainWindow);

	glfwPollEvents();

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

	glfwGetCursorPos(MainWindow, &_CursorPosX, &_CursorPosY);

	if (!_EventQueue.empty()) {
		switch (_EventQueue.front()->Type) {
		case EventType::START:
			printf("START EVENT\n");
			_EventQueue.pop();
			break;
		case EventType::EXIT:
			printf("EXIT EVENT\n");
			Active = false;
			glfwSetWindowShouldClose(MainWindow, GLFW_TRUE);
			_EventQueue.pop();
			break;
		default:
			break;
		}
	}
}

void EngineWindow::Terminate()
{
	glfwDestroyWindow(MainWindow);
	glfwTerminate();
}
