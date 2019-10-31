#include "Cyberwindow.h"


CyberWindow::CyberWindow(bool& _InitStatus, const char* _Title, const unsigned int _Width, const unsigned int _Height)
{
	_InitStatus = Init(_Title, _Width, _Height);
}

CyberWindow::~CyberWindow()
{
}

bool CyberWindow::Init(const char* _Title, const unsigned int _Width, const unsigned int _Height)
{
	if (!glfwInit()) {
		return false;
	}

	PlatformWindow = glfwCreateWindow(_Width, _Height, _Title, NULL, NULL);
	if (!PlatformWindow) {
		glfwTerminate();
		return false;
	}
	Width = _Width;
	Height = _Height;
	glfwMakeContextCurrent(PlatformWindow);

	SetVsync(true);

	//Anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback([](int _Error, const char* _Description){
		fprintf(stderr, "Glfw Error %d: %s\n", _Error, _Description);
		});

	glfwSetKeyCallback(PlatformWindow, [](GLFWwindow* _Window, int _Key, int _Scancode, int _Action, int _Mods) {
		if (_Key == GLFW_KEY_ESCAPE && _Action == GLFW_PRESS) {
			
		}
		});

	return true;
}

void CyberWindow::SetVsync(bool _Status)
{
	_Status ? glfwSwapInterval(1) : glfwSwapInterval(0);
	VsyncStatus = _Status;
}

bool CyberWindow::GetVsyncStatus()
{
	return VsyncStatus;
}

void CyberWindow::Update(std::queue<CyberEvent*>& _EventQueue)
{
	glfwSwapBuffers(PlatformWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwPollEvents();
	if (glfwGetKey(PlatformWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		_EventQueue.push(new CyberEvent(EventType::EXIT));
	}
	if (glfwGetKey(PlatformWindow, GLFW_KEY_W) == GLFW_PRESS) {
		_EventQueue.push(new CyberEvent(EventType::MOVE_FORWARD, EventTag::GRAPHICS));
	}
	if (glfwGetKey(PlatformWindow, GLFW_KEY_S) == GLFW_PRESS) {
		_EventQueue.push(new CyberEvent(EventType::MOVE_BACKWARD, EventTag::GRAPHICS));
	}
	if (glfwGetKey(PlatformWindow, GLFW_KEY_A) == GLFW_PRESS) {
		_EventQueue.push(new CyberEvent(EventType::MOVE_LEFT, EventTag::GRAPHICS));
	}
	if (glfwGetKey(PlatformWindow, GLFW_KEY_D) == GLFW_PRESS) {
		_EventQueue.push(new CyberEvent(EventType::MOVE_RIGHT, EventTag::GRAPHICS));
	}

	if (!_EventQueue.empty()) {
		switch (_EventQueue.front()->Type) {
		case EventType::START:
			printf("START EVENT\n");
			_EventQueue.pop();
			break;
		case EventType::EXIT:
			printf("EXIT EVENT\n");
			glfwSetWindowShouldClose(PlatformWindow, GLFW_TRUE);
			_EventQueue.pop();
			break;
		default:
			break;
		}
	}
}

void CyberWindow::Terminate()
{
	glfwDestroyWindow(PlatformWindow);
	glfwTerminate();
}
