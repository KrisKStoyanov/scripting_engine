#pragma once
#include "../../Core.h"
#include <memory>
#include "EngineWindow.h"

#include "../../Cyberspace/ImGUI/imgui.h"
#include "../../Cyberspace/ImGUI/imgui_impl_glfw.h"
#include "../../Cyberspace/ImGUI/imgui_impl_opengl3.h"

namespace Cyberspace {

	struct GUIProps {
		EngineWindow* RenderTarget;
		GUIProps(EngineWindow* _renderTarget = nullptr) :
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
		static GUIToolkit* Create(const GUIProps& _props = GUIProps());
		~GUIToolkit();
		void Init(const GUIProps& _props);
		void Configure(EngineWindow* _window);
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void Terminate();
		GUIState CurrentState = StartMenu;
	private:
		GUIToolkit(const GUIProps& _props);
	};
}

