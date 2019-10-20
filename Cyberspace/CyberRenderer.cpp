#include "CyberRenderer.h"

CyberRenderer::CyberRenderer()
{

}

CyberRenderer::~CyberRenderer()
{
}

void CyberRenderer::Activate()
{
	Configure();
}

void CyberRenderer::Configure()
{
	Shader* TestShader = new Shader("./Shaders/vert.glsl", "./Shaders/frag.glsl");
	CR_Shaders["TestShader"] = TestShader;
}

void CyberRenderer::Update(Entity* _Entity)
{
	CR_Shaders["TestShader"]->Activate();
	glBindVertexArray(_Entity->VAO);
	glDrawElements(GL_TRIANGLES, _Entity->IndexCollection.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	CR_Shaders["TestShader"]->Deactivate();
}

void CyberRenderer::Deactivate()
{
	for (std::pair<std::string, Shader*> S : CR_Shaders) {
		S.second->Clear();
	}
}

void CyberRenderer::AddShader(std::string _ShaderKey, Shader* _TargetShader)
{
	CR_Shaders[_ShaderKey] = _TargetShader;
}

void CyberRenderer::PrintProgramLog(GLuint _ProgramID)
{
	if (glIsProgram(_ProgramID)) {
		int InfoLogLength = 0;
		int MaxLength = InfoLogLength;

		glGetProgramiv(_ProgramID, GL_INFO_LOG_LENGTH, &MaxLength);

		char* InfoLog = new char[MaxLength];

		glGetProgramInfoLog(_ProgramID, MaxLength, &InfoLogLength, InfoLog);
		if (InfoLogLength > 0) {
			fprintf(stdout, "%s\n", InfoLog);
		}

		delete[] InfoLog;
	}
	else {
		fprintf(stdout, "%d is not a valid program ID\n", _ProgramID);
	}
}

void CyberRenderer::PrintShaderLog(GLuint _ShaderID)
{
	if (glIsShader(_ShaderID)) {
		int InfoLogLength = 0;
		int MaxLength = InfoLogLength;

		glGetShaderiv(_ShaderID, GL_INFO_LOG_LENGTH, &MaxLength);

		char* InfoLog = new char[MaxLength];

		glGetShaderInfoLog(_ShaderID, MaxLength, &InfoLogLength, InfoLog);
		if (InfoLogLength > 0) {
			fprintf(stdout, "%s\n", InfoLog);
		}

		delete[] InfoLog;
	}
	else {
		fprintf(stdout, "%d is not a valid shader ID\n", _ShaderID);
	}
}
