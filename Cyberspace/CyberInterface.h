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

class CyberInterface
{
public:
	CyberInterface(bool& _InitStatus);
	~CyberInterface();
	bool Init();
	void Configure();
	void Process(int _Key, int _Scancode, int _Action, int _Mods);
	void Update();
	void Terminate();
};

