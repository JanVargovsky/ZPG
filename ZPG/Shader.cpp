#include "Shader.h"

#include <iostream>
#include <string>

using namespace std;

Shader::Shader(const GLchar * code, const ShaderType shaderType)
	:type(shaderType)
{
	shader = glCreateShader(type);

	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	IsValid();
}

Shader::~Shader()
{
	glDeleteShader(shader);
}

bool Shader::IsValid() const
{
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		cerr << "Compilation of " << ToString(type) << " shader failed: " << infoLog << endl;
	}
	return success == GL_TRUE;
}

string Shader::ToString(const ShaderType type) const
{
	switch (type)
	{
	case ShaderType_Vertex:
		return "Vertex";
	case ShaderType_Fragment:
		return "Fragment";
	default:
		return "Unknown";
	}
}
