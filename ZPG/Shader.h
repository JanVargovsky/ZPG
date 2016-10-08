#pragma once
#include "ShaderLoader.h"
#include <GL/glew.h>
#include <string>

class Shader : private ShaderLoader
{
private:
	GLuint program;

public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual ~Shader();

	void UseProgram() const;

	// TODO: Remove
	const GLuint GetProgram() const
	{
		return program;
	}
};
