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
		bool VSync;
		bool Cursor;
		WindowProps(std::string _title = "Cyberspace",
			unsigned int _width = 1280,
			unsigned int _height = 720,
			bool _vsync = true,
			bool _cursor = true) :
			Width(_width), Height(_height), Title(_title),
			VSync(_vsync), Cursor(_cursor)
		{}
	};

	class CSPACE_API EngineWindow
	{
	public:
		EngineWindow(const WindowProps& _props = WindowProps());
		~EngineWindow();
		void Configure(const WindowProps& _props);
		void Terminate();
		
		inline bool GetCursor() { return m_Props.Cursor; }
		inline void SetCursor(bool _enable) {
			m_Props.Cursor = _enable;
			m_Props.Cursor ?
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL) :
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		inline bool GetVSync() { return m_Props.VSync; }
		inline void SetVSync(bool _enable) {
			m_Props.VSync = _enable;
			m_Props.VSync ?
				glfwSwapInterval(1) : glfwSwapInterval(0);
		}

		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, double& _CursorPosX, double& _CursorPosY);
		
		GLFWwindow* GetWindow();
		WindowProps GetWindowProps();

	private:
		GLFWwindow* m_Window = NULL;
		WindowProps m_Props;
	};
}


