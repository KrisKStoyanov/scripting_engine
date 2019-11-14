#pragma once
#include "../../Core.h"

#include "../../CyberEvent.h"
#include "../../Core.h"

#include "../../Cyberspace/ImGUI/imgui.h"
#include "../../Cyberspace/ImGUI/imgui_impl_glfw.h"
#include "../../Cyberspace/ImGUI/imgui_impl_opengl3.h"
#include "../Window/EngineWindow.h"

namespace Cyberspace {

	struct UIProps {
		UIProps() {}
	};

	class CSPACE_API UISystem
	{
	public:
		static UISystem* Create(const UIProps& _props = UIProps());
		UISystem(const UIProps& _props);
		~UISystem();
		void Init(const UIProps& _props);
		void Setup(EngineWindow* _window);
		void Configure();
		void OnUpdate(EngineWindow* _Window, std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void Terminate();

		bool m_StartGame = false;

		bool m_ShowStartMenu = true;
		bool m_ShowOptionsMenu = false;

		bool m_ShowWindowSettings = false;
		bool m_ShowGraphicsSettings = false;
		bool m_ShowAudioSettings = false;
	};
}

