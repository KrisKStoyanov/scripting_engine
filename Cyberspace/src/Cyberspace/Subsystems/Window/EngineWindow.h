#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <queue>
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
		void InitWindow(const WindowProps& _props);
		void Terminate();
		inline void SetVSync(bool _enable) {
			_enable ? glfwSwapInterval(1) : glfwSwapInterval(0);
			m_VSync = _enable;
		}
		inline bool GetVSync() { return m_VSync; }
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY);
		GLFWwindow* MainWindow = NULL;
		int m_WindowWidth = 0, m_WindowHeight = 0;
		bool m_VSync;
		bool m_ShowCursor = true;
		double CursorPosX, CursorPosY;
	};
}


