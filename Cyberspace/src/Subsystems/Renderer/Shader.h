#pragma once
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

class Shader {
public:
	Shader(const GLchar* _VertexShaderPath, const GLchar* _FragmentShaderPath);
	~Shader();

	GLuint ProgramID, VertexShaderID, FragmentShaderID;

	std::string ReadFile(const GLchar* _FilePath);

	void Activate();
	void Deactivate();

	void Clear();

	void PrintShaderLog(GLuint _ShaderID);
	void PrintProgramLog(GLuint _ProgramID);
};

