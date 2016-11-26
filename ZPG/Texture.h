#pragma once

#include <GL/glew.h>
#include <assimp/material.h>

class Texture
{
private:
	GLuint id;
	GLenum target;

public:
	Texture(GLenum target);
	~Texture();

	void Bind(int offset = 0);
	void Unbind();

	void SetImage(int width, int height, void *data, GLenum type);

private:
	void Initialize();
};

