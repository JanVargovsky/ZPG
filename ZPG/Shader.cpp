#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace glm;

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

void Shader::UnuseProgram() const
{
	glUseProgram(0);
}

void Shader::UseProgram(GLint program) const
{
	glUseProgram(program);
}

GLint Shader::GetCurrentProgram() const
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return id;
}

void Shader::Send(const GLchar * name, mat4 & value) const
{
	GLuint location = glGetUniformLocation(program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
}

void Shader::Send(const GLchar * name, glm::vec3 & value) const
{
	GLuint location = glGetUniformLocation(program, name);
	glUniform3fv(location, 1, value_ptr(value));
}
