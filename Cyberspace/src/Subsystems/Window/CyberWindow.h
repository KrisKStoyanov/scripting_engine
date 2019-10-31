#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <queue>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../CyberEvent.h"

//OGL SPECIFIC IMPLEMENTATION
class CyberWindow
{
public:
	CyberWindow(bool& _InitStatus, const char* _Title, const unsigned int _Width, const unsigned int _Height);
	~CyberWindow();
	bool Init(const char* _Title, const unsigned int _Width, const unsigned int _Height);
	void Terminate();
	void SetVsync(bool _Status);
	bool GetVsyncStatus();
	void Update(std::queue<CyberEvent*>& _EventQueue);
	GLFWwindow* PlatformWindow = NULL;
	unsigned int Width, Height;
	bool VsyncStatus;
	bool Active = false;
};

