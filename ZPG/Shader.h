#pragma once
#include "ShaderLoader.h"
#include <GL/glew.h>
#include <string>

class Shader: public ShaderLoader
{
private:
	GLuint program;

public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	virtual ~Shader();

	void Use();

	const GLuint GetProgram() const
	{
		return program;
	}

private:
	int CreateProgram(const int vertexShader, const int fragmentShader) const;
	bool CheckProgram(const int program) const;
};
