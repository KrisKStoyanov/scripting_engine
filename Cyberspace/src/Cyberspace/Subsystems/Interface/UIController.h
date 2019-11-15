#pragma once
#include "../../Core.h"
#include <string>
#include <unordered_map>
#include "EngineWindow.h"

namespace Cyberspace {

	struct UIProps {
		WindowProps windowProps;
		bool VSync;
		bool Cursor;
		UIProps(
			WindowProps _windowProps = WindowProps(), 
			bool _vsync = true,
			bool _cursor = true) 
		: windowProps(_windowProps),
		VSync (_vsync),
		Cursor (_cursor) {}
	};
	class CSPACE_API UIController
	{
	public:
		static UIController* Create(const UIProps& _props = UIProps());
		void Init(const UIProps& _props);
		void CreateWindow(const WindowProps& _props, bool _setFocus = true);
		void DeleteWindow(std::string _tag);
		void SetGraphicsContext(EngineWindow* _window);

		inline bool GetVSync() { return m_VSync; }
		void SetVSync(bool _enable);

		bool GetCursor() { return m_Cursor; }
		void SetCursor(bool _enable);

		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void Terminate();
		std::string FocusedWindow;
		std::unordered_map<std::string, EngineWindow*> AvailableWindows;
		double CursorPosX, CursorPosY;
		~UIController();
	private:
		UIController(const UIProps& _props);
		bool m_Cursor;
		bool m_VSync;
	};
}

