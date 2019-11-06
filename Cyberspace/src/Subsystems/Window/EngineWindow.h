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

//OGL FOR WINDOWS - IMPLEMENTATION
class EngineWindow
{
public:
	EngineWindow(bool& _InitStatus, const char* _Title, const unsigned int _Width, const unsigned int _Height);
	~EngineWindow();
	bool Init(const char* _Title, const unsigned int _Width, const unsigned int _Height);
	void Terminate();
	void SetVsync(bool _Status);
	bool GetVsyncStatus();
	void Update(std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY);
	GLFWwindow* MainWindow = NULL;
	unsigned int Width, Height;
	bool VsyncStatus;
	double CursorPosX, CursorPosY;
	bool ToggleRepeat = false;
	bool Active = false;
};

