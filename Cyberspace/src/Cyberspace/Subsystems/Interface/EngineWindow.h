#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../CyberEvent.h"
#include "../../../EngineProps.h"

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
		void Configure(const GraphicsProps& _props);
		void Terminate();

		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, EngineState _state);
		double CursorPosX, CursorPosY;
		GLFWwindow* GetNativeWindow();
	private:
		EngineWindow(const GraphicsProps& _props);
		GLFWwindow* m_Window = NULL;
	};
}


