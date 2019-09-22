#include "Shader.h"

Shader::Shader(const GLchar* _VertFilePath, const GLchar* _FragFilePath)
{
	ProgramID = glCreateProgram();

	std::string VertShaderSource;

	try {
		VertShaderSource = ReadFile(_VertFilePath);
	}
	catch (std::ifstream::failure _error) {
		std::cout << "Error: Unable to read Vertex Shader file " << std::endl;
	}

	VertShaderID = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* VertSourceCode = VertShaderSource.c_str();
	glShaderSource(VertShaderID, 1, &VertSourceCode, NULL);

	GLint CompileStatus = 0;
	glCompileShader(VertShaderID);
	glGetShaderiv(VertShaderID, GL_COMPILE_STATUS, &CompileStatus);

	if (!CompileStatus) {
		std::cout << "Error: Unable to compile Verter Shader\n" << PrintShaderLog(VertShaderID) << std::endl;
	}

	glAttachShader(ProgramID, VertShaderID);
	glDeleteShader(VertShaderID);

	std::string FragShaderSource;

	try {
		FragShaderSource = ReadFile(_FragFilePath);
	}
	catch (std::ifstream::failure _error) {
		std::cout << "Error: Unable to read Fragment Shader file " << std::endl;
	}

	FragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* FragSourceCode = FragShaderSource.c_str();
	glShaderSource(FragShaderID, 1, &FragSourceCode, NULL);

	glCompileShader(FragShaderID);
	glGetShaderiv(FragShaderID, GL_COMPILE_STATUS, &CompileStatus);

	if (!CompileStatus) {
		std::cout << "Error: Unable to compile Fragment Shader\n" << PrintShaderLog(FragShaderID) << std::endl;
	}

	glAttachShader(ProgramID, VertShaderID);
	glDeleteShader(FragShaderID);

	GLint LinkStatus = 0;
	glLinkProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &LinkStatus);
	if (!LinkStatus) {
		std::cout << "Error: Unable to link shader program\n" << PrintProgramLog(ProgramID) << std::endl;
	}
}

Shader::~Shader()
{
}

std::string Shader::ReadFile(const GLchar* _FilePath)
{
	std::ifstream FileParser;
	std::stringstream FileBuffer;
	FileParser.exceptions(std::ifstream::badbit); 
	FileParser.open(_FilePath);
	FileBuffer << FileParser.rdbuf();
	FileParser.close();
	std::string FileContent = FileBuffer.str();
	return FileContent;
}

void Shader::Activate()
{
	glUseProgram(ProgramID);
}

void Shader::Deactivate()
{
	glUseProgram(0);	
	glDeleteProgram(ProgramID);
}

std::string Shader::PrintShaderLog(GLuint _ShaderID)
{
	int LogLength;
	glGetShaderiv(_ShaderID, GL_INFO_LOG_LENGTH, &LogLength);
	GLchar* ErrorLog = new GLchar[LogLength];
	glGetShaderInfoLog(_ShaderID, LogLength, &LogLength, ErrorLog);
	return ErrorLog;
}

std::string Shader::PrintProgramLog(GLuint _ProgramID)
{
	int LogLength;
	glGetProgramiv(_ProgramID, GL_INFO_LOG_LENGTH, &LogLength);
	GLchar* ErrorLog = new GLchar[LogLength];
	glGetProgramInfoLog(_ProgramID, LogLength, &LogLength, ErrorLog);
	return ErrorLog;
}

