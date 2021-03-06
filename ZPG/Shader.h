#pragma once

#include <GL/glew.h>

#include <string>

enum ShaderType {
	ShaderType_Vertex = GL_VERTEX_SHADER,
	ShaderType_Fragment = GL_FRAGMENT_SHADER,
	ShaderType_Geometry = GL_GEOMETRY_SHADER,
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

