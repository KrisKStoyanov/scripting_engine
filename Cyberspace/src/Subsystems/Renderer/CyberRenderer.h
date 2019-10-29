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
#include "Shader.h"

#include "../../Entity.h"

class CyberRenderer
{
public:
	CyberRenderer(bool& _InitStatus);
	~CyberRenderer();
	bool Init();
	void Configure();
	void Update(std::map<std::string, Entity*> _EntityCollection);
	void Terminate();
	void AddShader(std::string _ShaderKey, Shader* _TargetShader);
	void PrintProgramLog(GLuint _ProgramID);
	void PrintShaderLog(GLuint _ShaderID);
	std::map<std::string, Shader*> CR_Shaders;
};

