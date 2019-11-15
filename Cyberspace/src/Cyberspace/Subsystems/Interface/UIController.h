#pragma once
#include "../../Core.h"
#include <string>
#include <unordered_map>
#include "EngineWindow.h"

namespace Cyberspace {

	class CSPACE_API UIController
	{
	public:
		static UIController* Create(const UIProps& _props = UIProps());
		void Init(const UIProps& _props);
		void CreateWindow(const WindowProps& _props, bool _setFocus = true);
		void DeleteWindow(std::string _tag);
		void SetGraphicsContext(EngineWindow* _window);

		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void Terminate();
		std::string FocusedWindow;
		std::unordered_map<std::string, EngineWindow*> AvailableWindows;
		double CursorPosX, CursorPosY;
		~UIController();
	private:
		UIController(const UIProps& _props);
	};
}

