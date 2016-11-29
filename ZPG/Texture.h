#pragma once

#include <GL/glew.h>
#include <assimp/material.h>

enum TextureType {
	TextureType_Diffuse,
	TextureType_Specular,
	TextureType_Normal,
	TextureType_Cube,
	TextureType_Unknown,
};

class Texture
{
private:
	GLuint id;
	GLenum target;
	TextureType type;

public:
	Texture(GLenum target, TextureType type);
	~Texture();

	void Bind(int offset = 0);
	void Unbind();

	void SetImage(int width, int height, void *data, GLenum type);
	void Send(GLenum target, GLenum pname, GLint param);

private:
	void Initialize();
	std::string ToString(TextureType type);
};

