#pragma once
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(const GLchar* _VertexShaderPath, const GLchar* _FragmentShaderPath);
	~Shader();

	GLuint ProgramID, VertexShaderID, FragmentShaderID;
	GLuint ProjectionMatrixLoc, ViewMatrixLoc, ModelMatrixLoc;

	std::string ReadFile(const GLchar* _FilePath);

	void Activate();
	void Update(glm::mat4 _ModelMatrix, glm::mat4 _ViewMatrix, glm::mat4 _ProjectionMatrix);
	void Deactivate();

	void Clear();

	void PrintShaderLog(GLuint _ShaderID);
	void PrintProgramLog(GLuint _ProgramID);
};

