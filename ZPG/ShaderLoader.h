#pragma once
#include "Shader.h"

#include <GL/glew.h>
#include <string>
#include <memory>


class ShaderLoader
{
public:
	std::unique_ptr<Shader> CreateShader(const GLchar *path, ShaderType type) const;

public:
	std::string GetContent(const GLchar * path) const;
};
