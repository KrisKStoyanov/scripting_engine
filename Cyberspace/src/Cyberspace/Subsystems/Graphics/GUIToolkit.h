#pragma once
#include "../Interface/EngineWindow.h"

#include "../../Cyberspace/ImGUI/imgui.h"
#include "../../Cyberspace/ImGUI/imgui_impl_glfw.h"
#include "../../Cyberspace/ImGUI/imgui_impl_opengl3.h"

namespace Cyberspace {

	enum class CSPACE_API GUIState : int {
		None = 0,
		StartMenu,
		Settings,
		VideoSettings,
		AudioSettings,
		Gameplay,
		EditScript,
		PauseMenu,
	};

	class CSPACE_API GUIToolkit
	{
	public:
		static GUIToolkit* Create(EngineWindow* _window, const GraphicsProps& _props = GraphicsProps());
		~GUIToolkit();
		void Init(EngineWindow* _window, const GraphicsProps& _props);
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, EngineProps& _props);
		void Terminate();
		
		char buf1[64] = "";
		char buf2[512] = "";
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
		void ProduceScript(char nameBuf[64], char contentbuf[512]);

		inline GUIState GetState() { return m_State; }
		inline void SetState(GUIState _state) { m_State = _state; }

	private:
		GUIState m_State = GUIState::StartMenu;
		GUIToolkit(EngineWindow* _window, const GraphicsProps& _props);

		bool showDemo = true;
	};
}

