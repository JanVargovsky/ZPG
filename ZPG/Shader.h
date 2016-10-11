#pragma once

#include <GL/glew.h>

#include <string>

enum ShaderType {
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
};

class Shader
{
private:
	ShaderType type;
	int shader;

public:
	Shader(const GLchar *code, const ShaderType shaderType);
	~Shader();

	bool IsValid() const;

	inline ShaderType GetShaderType() { return type; }
	inline int GetShaderId() { return shader; }
private:
	std::string ToString(const ShaderType type) const;
};

