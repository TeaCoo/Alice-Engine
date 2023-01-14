#pragma once
#include "Alice/FileIO/FileReader.h"
#include <glad/glad.h>
namespace Alice
{
	static unsigned int CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile "<<
				(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
				<<" shader!" << std::endl;
			std::cout << message << std::endl;
		}
	
		return id;
	}

	static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
	class ShaderProcessor
	{
	public:
		ShaderProcessor(std::string vertPath, std::string fragPath);
		std::string getText(std::fstream& fileStream);
	public:
		std::string vert;
		std::string frag;
	};
}


