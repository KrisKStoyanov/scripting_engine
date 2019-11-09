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

#include "../../Core.h"

namespace Cyberspace {
	//OGL FOR WINDOWS - IMPLEMENTATION
	struct WindowProps {
		std::string Title;
		unsigned int Width, Height;
		bool VSyncStatus;

		WindowProps(std::string _title = "Cyberspace",
			unsigned int _width = 1280,
			unsigned int _height = 720,
			bool _vSyncStatus = true) :
			Title(_title), Width(_width), Height(_height), VSyncStatus(_vSyncStatus) {}
	};

	class CSPACE_API EngineWindow
	{
	public:
		static EngineWindow* Create(const WindowProps& _props = WindowProps());
		EngineWindow(const WindowProps& _props);
		~EngineWindow();
		void Init(const WindowProps& _props);
		void Terminate();
		void SetVSync(bool _enable);
		bool GetVSync();
		void Update(std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY);
		GLFWwindow* MainWindow = NULL;
		bool VSyncStatus;
		double CursorPosX, CursorPosY;
		bool Active = false;
	};
}

