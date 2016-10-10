#pragma once
#include "ShaderLoader.h"

#include <GL/glew.h>
#include <string>
#include <glm/mat4x4.hpp>

class Program : private ShaderLoader
{
private:
	GLuint program;

public:
	Program(const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual ~Program();

	void Use() const;
	void Unuse() const;
	void Send(const GLchar* name, glm::mat4 & value) const;
	void Send(const GLchar* name, glm::vec3 & value) const;

private:
	int CreateProgram(const int vertexShader, const int fragmentShader) const;
	bool CheckProgram(const int program) const;

	GLint GetCurrentProgram() const;
	void Use(GLint program) const;
};
