#pragma once
#include "../../Core.h"
#include <string>
#include <unordered_map>
#include "EngineWindow.h"
#include "GUIToolkit.h"

namespace Cyberspace {

	struct UIProps {
		WindowProps PrimaryWindowProps;
		GUIProps GuiProps;
		UIProps(
			WindowProps _windowProps = WindowProps(),
			GUIProps _guiProps = GUIProps()) 
		: PrimaryWindowProps(_windowProps) {}
	};
	class CSPACE_API UIController
	{
	public:
		static UIController* Create(const UIProps& _props = UIProps());
		void Init(const UIProps& _props);
		void SetGraphicsContext(EngineWindow* _window);
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void OnUpdateGUI(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void Terminate();
		std::string FocusedWindow = "Primary";
		std::unordered_map<std::string, EngineWindow*> AvailableWindows;
		double CursorPosX, CursorPosY;
		std::unique_ptr<GUIToolkit> m_GUIToolkit;
		UIController(const UIProps& _props);
		~UIController();
	};
}

