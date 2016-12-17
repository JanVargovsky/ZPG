#pragma once

#include <GL/glew.h>
#include <assimp/material.h>

enum TextureType {
	TextureType_Custom, // Used for custom naming
	TextureType_Diffuse,
	TextureType_Specular,
	TextureType_Normal,
	TextureType_Cube,
	TextureType_TerrainX,
	TextureType_TerrainY,
	TextureType_TerrainZ,
	TextureType_Unknown,
};

class Texture
{
private:
	GLuint id;
	GLenum target;
	TextureType type;
	std::string name;

public:
	Texture(GLenum target, TextureType type, std::string name);
	Texture(GLenum target, TextureType type);
	Texture(GLenum target, std::string name);
	~Texture();

	void Bind(int offset = 0);
	void Unbind();

	void SetImage(int width, int height, void *data, GLenum type);
	void Send(GLenum target, GLenum pname, GLint param);

private:
	void Initialize();
	std::string ToString(TextureType type);
	std::string GetTextureName();
};

