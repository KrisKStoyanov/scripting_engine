#include "Shader.h"

namespace Cyberspace {
	Shader::Shader(std::string _vertexSrc, std::string _fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = _vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			CSPACE_CORE_ERROR("Vertex Source: {0} - failed compilation. {1}", _vertexSrc, infoLog.data());
			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = _fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			CSPACE_CORE_ERROR("Fragment Source: {0} - failed compilation. {1}", _fragmentSrc, infoLog.data());
			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		ProgramID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(ProgramID, vertexShader);
		glAttachShader(ProgramID, fragmentShader);

		// Link our program
		glLinkProgram(ProgramID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(ProgramID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(ProgramID, maxLength, &maxLength, &infoLog[0]);
			CSPACE_CORE_ERROR("Program failed to link! {0}", infoLog.data());
			// We don't need the program anymore.
			glDeleteProgram(ProgramID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(ProgramID, vertexShader);
		glDetachShader(ProgramID, fragmentShader);
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

	void Shader::Clear()
	{
		glUseProgram(0);
		glDeleteProgram(ProgramID);
	}
}

