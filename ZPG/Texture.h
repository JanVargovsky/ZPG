#pragma once

#include <GL/glew.h>
#include <assimp/material.h>

class Texture
{
private:
	GLuint id;
	//aiTextureType type;
	//std::string path;
	GLenum target;

public:
	Texture();
	~Texture();

	void Bind(int offset = 0);
	void Unbind();

	void SetImage(int width, int height, void *data);

private:
	void Initialize();
};

