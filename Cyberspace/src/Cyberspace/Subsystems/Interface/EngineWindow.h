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

//Windows implementation - [GLFW Powered]
namespace Cyberspace {

	struct WindowProps {
		int Width;
		int Height;
		std::string Title;
		WindowProps(std::string _title = "Cyberspace",
			unsigned int _width = 1280,
			unsigned int _height = 720) :
			Width(_width), Height(_height), Title(_title)
		{}
	};

	class CSPACE_API EngineWindow
	{
	public:
		EngineWindow(const WindowProps& _props = WindowProps());
		~EngineWindow();
		void Configure(const WindowProps& _props);
		void Terminate();

		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY);
		
		GLFWwindow* GetNativeWindow();
		WindowProps GetWindowProps();

	private:
		GLFWwindow* m_Window = NULL;
		WindowProps m_Props;
	};
}


