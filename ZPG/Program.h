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
	static Program *current;
	GLuint program;
	std::vector<std::unique_ptr<Shader>> shaders;

public:
	Program(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar *geometryPath = "");
	Program(const std::string pathToShadersWithNameWithoutExtension);
	~Program();

	static Program* Current();

	bool Compile();

	void Use();
	void Unuse();
	void Send(const GLchar* name, glm::mat4 & value);
	void Send(const GLchar* name, glm::vec3 & value);
	void Send(const GLchar* name, int value);
	void Send(const GLchar* name, float value);

private:
	bool CheckProgram(const int program);

	GLint GetCurrentProgram();
	//void Use(GLint program);
};
