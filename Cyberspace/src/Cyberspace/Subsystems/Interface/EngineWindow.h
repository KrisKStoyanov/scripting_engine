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
#include "../Graphics/GraphicsContext.h"

#include "../../Cyberspace/ImGUI/imgui.h"
#include "../../Cyberspace/ImGUI/imgui_impl_glfw.h"
#include "../../Cyberspace/ImGUI/imgui_impl_opengl3.h"

namespace Cyberspace {

	class CSPACE_API EngineWindow
	{
	public:
		static EngineWindow* Create(const GraphicsProps& _props = GraphicsProps());
		~EngineWindow();
		void Init(const GraphicsProps& _props);
		void Recreate(const GraphicsProps& _props);
		void Terminate();

		inline bool GetVSync() { return m_VSync; }
		void SetVSync(bool _enable);

		inline bool GetCursorEnabled() { return m_Cursor; }
		void SetCursorEnabled(bool _enable);

		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		double CursorPosX, CursorPosY;
		GLFWwindow* GetNativeWindow();
	private:
		EngineWindow(const GraphicsProps& _props);
		bool m_VSync;
		bool m_Cursor;

		GLFWwindow* m_Window = NULL;
	};
}


