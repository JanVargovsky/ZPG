#pragma once
#include "ShaderLoader.h"

#include <GL/glew.h>
#include <string>
#include <glm/mat4x4.hpp>

class Shader : private ShaderLoader
{
private:
	GLuint program;

public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual ~Shader();

	void UseProgram() const;
	void UnuseProgram() const;
	void Send(const GLchar* name, glm::mat4 & value) const;
	void Send(const GLchar* name, glm::vec3 & value) const;

private:
	GLint GetCurrentProgram() const;
	void UseProgram(GLint program) const;
};
