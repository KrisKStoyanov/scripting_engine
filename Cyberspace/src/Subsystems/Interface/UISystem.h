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

class UISystem
{
public:
	UISystem(bool& _InitStatus);
	~UISystem();
	bool Init();
	void Configure();
	void Update();
	void Terminate();
};

