#pragma once
#include "../../Core.h"
#include <string>
#include <unordered_map>
#include "EngineWindow.h"

namespace Cyberspace {

	class CSPACE_API UIController
	{
	public:
		static UIController* Create(const WindowProps& _props = WindowProps());
		void Init(const WindowProps& _props);		
		void Restart(const WindowProps& _props); 
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void Terminate();
		
		inline EngineWindow*& GetWindow() { return m_Window; }

		double CursorPosX, CursorPosY;
		~UIController();
	private:
		EngineWindow* m_Window;
		UIController(const WindowProps& _props);
	};
}

