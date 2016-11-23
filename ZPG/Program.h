#pragma once
#include "ShaderLoader.h"

#include <GL/glew.h>
#include <string>
#include <glm/mat4x4.hpp>
#include <vector>
#include <memory>

class Program
{
private:
	GLuint program;
	std::vector<std::unique_ptr<Shader>> shaders;

public:
	Program(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Program();

	bool Compile();

	void Use() const;
	void Unuse() const;
	void Send(const GLchar* name, glm::mat4 & value) const;
	void Send(const GLchar* name, glm::vec3 & value) const;
	void Send(const GLchar* name, int value) const;
	void Send(const GLchar* name, float value) const;

private:
	bool CheckProgram(const int program) const;

	GLint GetCurrentProgram() const;
	void Use(GLint program) const;
};
