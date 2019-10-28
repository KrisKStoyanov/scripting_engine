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

void CyberWindow::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(PlatformWindow);
}

void CyberWindow::Terminate()
{
	glfwDestroyWindow(PlatformWindow);
	glfwTerminate();
}
