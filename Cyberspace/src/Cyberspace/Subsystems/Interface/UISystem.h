#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../CyberEvent.h"
#include "../../Core.h"

#include "../../Cyberspace/ImGUI/imgui.h"
#include "../../Cyberspace/ImGUI/imgui_impl_glfw.h"
#include "../../Cyberspace/ImGUI/imgui_impl_opengl3.h"
#include <queue>
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
		void OnUpdate(std::queue<CyberEvent*>& _eventQueue);
		void Terminate();
	};
}

