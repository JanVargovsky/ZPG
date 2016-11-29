#include "Program.h"
#include "DependencyResolver.h"
#include "ErrorChecker.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace glm;

Program* Program::current = nullptr;

Program::Program(const GLchar * vertexPath, const GLchar * fragmentPath)
	:program(-1)
{
	ShaderLoader *shaderLoader = DependencyResolver::GetInstance().Resolve<ShaderLoader*>();
	unique_ptr<Shader> vertex = shaderLoader->CreateShader(vertexPath, ShaderType_Vertex);
	unique_ptr<Shader> fragment = shaderLoader->CreateShader(fragmentPath, ShaderType_Fragment);

	shaders.push_back(move(vertex));
	shaders.push_back(move(fragment));

	Compile();
	ErrorChecker::CheckOpenGLError();
}

Program::Program(const string pathToShadersWithNameWithoutExtension)
	:Program((const GLchar*)(pathToShadersWithNameWithoutExtension + ".vert").c_str(), (const GLchar*)(pathToShadersWithNameWithoutExtension + ".frag").c_str())
{
}

Program::~Program()
{
	glUseProgram(0);
	glDeleteProgram(program);
}

Program * Program::Current()
{
	return current;
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

void Program::Use()
{
	current = this;
	glUseProgram(program);
}

void Program::Unuse()
{
	current = nullptr;
	glUseProgram(0);
}

bool Program::CheckProgram(const int program)
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

GLint Program::GetCurrentProgram()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return id;
}

void Program::Send(const GLchar * name, mat4 & value)
{
	GLuint location = glGetUniformLocation(program, name);
	ErrorChecker::CheckOpenGLError();
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
	ErrorChecker::CheckOpenGLError();
}

void Program::Send(const GLchar * name, glm::vec3 & value)
{
	GLuint location = glGetUniformLocation(program, name);
	ErrorChecker::CheckOpenGLError();
	glUniform3fv(location, 1, value_ptr(value));
	ErrorChecker::CheckOpenGLError();
}

void Program::Send(const GLchar * name, int value)
{
	GLuint location = glGetUniformLocation(program, name);
	ErrorChecker::CheckOpenGLError();
	glUniform1i(location, value);
	ErrorChecker::CheckOpenGLError();
}

void Program::Send(const GLchar * name, float value)
{
	GLuint location = glGetUniformLocation(program, name);
	ErrorChecker::CheckOpenGLError();
	glUniform1f(location, value);
	ErrorChecker::CheckOpenGLError();
}
