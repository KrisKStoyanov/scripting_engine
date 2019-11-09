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

#include "../Graphics/Renderer.h"
#include "../Physics/PhysicsSystem.h"
#include "../Audio/AudioSystem.h"
#include "../Networking/CyberNet.h"
#include "../../CyberEvent.h"
#include "../../Core.h"

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
		void Configure();
		void Update();
		void Terminate();
	};
}

