#pragma once
#include <GL/glew.h>
#include <string>

class ShaderLoader
{
public:
	std::string GetContent(const GLchar * path) const;

	enum ShaderType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
	};
	std::string ToString(const ShaderType type) const;

	int CreateShader(const GLchar *path, ShaderType type) const;
	bool CheckShader(const int shader, const ShaderType type) const;

	int CreateProgram(const int vertexShader, const int fragmentShader) const;
	bool CheckProgram(const int program) const;
};
