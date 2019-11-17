#pragma once
#include "../../Core.h"
#include <memory>
#include "../Interface/EngineWindow.h"

#include "../../Cyberspace/ImGUI/imgui.h"
#include "../../Cyberspace/ImGUI/imgui_impl_glfw.h"
#include "../../Cyberspace/ImGUI/imgui_impl_opengl3.h"
#include <string>

namespace Cyberspace {

	enum class GUIState : int {
		None = 0,
		StartMenu,
		Settings,
		Gameplay,
		PauseMenu,
	};

	struct ResDisplayFormat {
		const char* DisplayFormat;
		int ResX;
		int ResY;
	};

	class CSPACE_API GUIToolkit
	{
	public:
		static GUIToolkit* Create(EngineWindow* _window, const GraphicsProps& _props = GraphicsProps());
		~GUIToolkit();
		void Init(EngineWindow* _window, const GraphicsProps& _props);
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, EngineProps& _props);
		void Terminate();
		
		inline GUIState GetState() { return m_State; }
		inline void SetState(GUIState _state) { m_State = _state; }

	private:
		GUIState m_State = GUIState::StartMenu;
		GUIToolkit(EngineWindow* _window, const GraphicsProps& _props);

		const char* m_CurrentRes;
		const char* m_Resolutions[3] = { "1600x900", "1280x720", "800x600" };
		bool showDemo = true;
	};
}

