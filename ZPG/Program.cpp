#include "Program.h"
#include "DependencyResolver.h"
#include "ErrorChecker.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace glm;

Program::Program(const GLchar * vertexPath, const GLchar * fragmentPath)
	:program(-1)
{
	ShaderLoader *shaderLoader = DependencyResolver::GetInstance().Resolve<ShaderLoader*>();
	unique_ptr<Shader> vertex = shaderLoader->CreateShader(vertexPath, ShaderType::Vertex);
	unique_ptr<Shader> fragment = shaderLoader->CreateShader(fragmentPath, ShaderType::Fragment);

	shaders.push_back(move(vertex));
	shaders.push_back(move(fragment));

	Compile();
}

Program::~Program()
{
	glUseProgram(0);
	glDeleteProgram(program);
}

bool Program::Compile()
{
	GLuint shaderProgram = glCreateProgram();

	for (auto & shader : shaders)
		glAttachShader(shaderProgram, shader->GetShaderId());

	glLinkProgram(shaderProgram);
	if (!CheckProgram(shaderProgram))
		return false;

	program = shaderProgram;
	return false;
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

	ErrorChecker::CheckOpenGLError();
}

void Program::Send(const GLchar * name, glm::vec3 & value) const
{
	GLuint location = glGetUniformLocation(program, name);
	glUniform3fv(location, 1, value_ptr(value));

	ErrorChecker::CheckOpenGLError();
}

void Program::Send(const GLchar * name, int value) const
{
	GLuint location = glGetUniformLocation(program, name);
	glUniform1i(location, value);

	ErrorChecker::CheckOpenGLError();
}
