#pragma once
#include <GL/glew.h>
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
#include "../../../EngineProps.h"
#include "../../Core.h"

//Windows implementation - [GLFW Powered]
namespace Cyberspace {

	class CSPACE_API EngineWindow
	{
	public:
		static EngineWindow* Create(const WindowProps& _props = WindowProps());
		EngineWindow(const WindowProps& _props);
		~EngineWindow();
		void Init(const WindowProps& _props);
		void Recreate(const WindowProps& _props);
		void Terminate();

		inline bool GetVSync() { return m_VSync; }
		void SetVSync(bool _enable);

		inline bool GetCursorEnabled() { return m_Cursor; }
		void SetCursorEnabled(bool _enable);

		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue,
		double _cursorPosX, double _cursorPosY);

		GLFWwindow* GetNativeWindow();
		WindowProps GetWindowProps();
	private:
		bool m_VSync;
		bool m_Cursor;
		
		WindowProps m_Props;
		GLFWwindow* m_Window = NULL;
	};
}


