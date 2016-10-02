#include "Shader.h"

#include <iostream>

using namespace std;

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	int vertexShader = CreateShader(vertexPath, Vertex);
	int fragmentShader = CreateShader(fragmentPath, Fragment);

	program = CreateProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(program);
}

void Shader::Use()
{
	glUseProgram(program);
}

int Shader::CreateProgram(const int vertexShader, const int fragmentShader) const
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	CheckProgram(shaderProgram);
	return shaderProgram;
}

bool Shader::CheckProgram(const int program) const
{
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cerr << "Compilation of program linking failed: " << infoLog << endl;
	}
	return success == GL_TRUE;
}
