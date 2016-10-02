#pragma once
#include <GL/glew.h>
#include <string>

class ShaderLoader
{
public:
	virtual ~ShaderLoader();

protected:
	enum ShaderType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
	};

	int CreateShader(const GLchar *path, ShaderType type) const;

private:
	std::string GetContent(const GLchar * path) const;
	bool CheckShader(const int shader, const ShaderType type) const;
	std::string ToString(const ShaderType type) const;
};
