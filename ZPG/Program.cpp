#include "Program.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace glm;

Program::Program(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	int vertexShader = CreateShader(vertexPath, Vertex);
	int fragmentShader = CreateShader(fragmentPath, Fragment);

	program = CreateProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Program::~Program()
{
	glUseProgram(0);
	glDeleteProgram(program);
}

int Program::CreateProgram(const int vertexShader, const int fragmentShader) const
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	CheckProgram(shaderProgram);
	return shaderProgram;
}

bool Program::CheckProgram(const int program) const
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

void Program::Use() const
{
	glUseProgram(program);
}

void Program::Unuse() const
{
	glUseProgram(0);
}

void Program::Use(GLint program) const
{
	glUseProgram(program);
}

GLint Program::GetCurrentProgram() const
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return id;
}

void Program::Send(const GLchar * name, mat4 & value) const
{
	GLuint location = glGetUniformLocation(program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
}

void Program::Send(const GLchar * name, glm::vec3 & value) const
{
	GLuint location = glGetUniformLocation(program, name);
	glUniform3fv(location, 1, value_ptr(value));
}
