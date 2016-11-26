#include "Texture.h"

Texture::Texture(GLenum target)
	:target(target)
{
	Initialize();
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Initialize()
{
	glGenTextures(1, &id);
}

void Texture::Bind(int offset)
{
	glActiveTexture(GL_TEXTURE0 + offset);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind()
{
}

void Texture::SetImage(int width, int height, void * data, GLenum type)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(type, // Type of texture 1D, 2D, 3D
		0, // Pyramid level (for mip-mapping) - 0 is the top level
		GL_RGB, // Internal colour format to convert to
		width, // Image width i.e. 640
		height, // Image height i.e. 480
		0, // Border width in pixels (can either be 1 or 0)
		GL_BGR, // Input format (GL_RGB, GL_RGBA, GL_BGR etc.)
		GL_UNSIGNED_BYTE, // Image data type
		data);

	glGenerateMipmap(GL_TEXTURE_2D);
}

