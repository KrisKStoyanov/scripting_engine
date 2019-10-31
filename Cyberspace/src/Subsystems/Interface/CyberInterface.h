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

#include "../Renderer/CyberRenderer.h"
#include "../Physics/CyberPhysics.h"
#include "../Audio/CyberAudio.h"
#include "../Networking/CyberNet.h"
#include "../../CyberEvent.h"

class CyberInterface
{
public:
	CyberInterface(bool& _InitStatus);
	~CyberInterface();
	bool Init();
	void Configure();
	void Update();
	void Terminate();
};

