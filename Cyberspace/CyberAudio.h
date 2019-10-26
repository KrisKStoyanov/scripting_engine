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

#include <fmod.hpp>

class CyberAudio
{
public:
	CyberAudio();
	~CyberAudio();
	void Activate();
	void Configure();
	void Update();
	void Deactivate();
};

