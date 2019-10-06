#pragma once
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

class Shader {
public:
	Shader(const GLchar* _VertFilePath, const GLchar* _FragFilePath);
	~Shader();

	GLuint ProgramID, VertShaderID, FragShaderID;

	std::string ReadFile(const GLchar* _FilePath);

	void Activate();
	void Deactivate();

	void Clear();

	std::string PrintShaderLog(GLuint _ShaderID);
	std::string PrintProgramLog(GLuint _ProgramID);
};

