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

void Shader::UseProgram() const
{
	glUseProgram(program);
}