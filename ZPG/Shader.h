#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
private:
	GLuint program;

	enum ShaderType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
	};
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();

	void Use();

	const GLuint GetProgram() const
	{
		return program;
	}

private:
	std::string GetContent(const GLchar * path) const;
	int CreateShader(const GLchar *code, ShaderType type) const;
	bool CheckShader(const int shader, const ShaderType type) const;
	int CreateProgram(const int vertexShader, const int fragmentShader) const;
	bool CheckProgram(const int program) const;
	std::string ToString(const ShaderType type) const;
};
