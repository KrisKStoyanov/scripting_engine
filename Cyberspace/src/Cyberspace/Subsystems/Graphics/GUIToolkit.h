#pragma once
#include "../../Core.h"
#include <memory>
#include "../Interface/EngineWindow.h"

#include "../../Cyberspace/ImGUI/imgui.h"
#include "../../Cyberspace/ImGUI/imgui_impl_glfw.h"
#include "../../Cyberspace/ImGUI/imgui_impl_opengl3.h"
#include <string>

namespace Cyberspace {

	struct GUIProps {
		std::string RenderTarget;
		GUIProps(std::string _renderTarget = "Cyberspace") :
		RenderTarget(_renderTarget) {}
	};

	enum GUIState : int {
		None = 0,
		StartMenu,
		Settings,
		Gameplay,
		PauseMenu,
	};

	class CSPACE_API GUIToolkit
	{
	public:
		static GUIToolkit* Create(EngineWindow* _window, const GUIProps& _props = GUIProps());
		~GUIToolkit();
		void Init(EngineWindow* _window, const GUIProps& _props);
		void Configure(EngineWindow* _window);
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void Terminate();
		GUIState CurrentState = StartMenu;
	private:
		GUIToolkit(EngineWindow* _window, const GUIProps& _props);
	};
}

