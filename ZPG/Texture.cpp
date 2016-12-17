#include "Texture.h"
#include "Program.h"
#include "Logger.h"

using namespace std;

Texture::Texture(GLenum target, TextureType type)
	:target(target), type(type)
{
	Initialize();
	Logger::Verbose("Created " + ToString(type) + " texture");
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Initialize()
{
	glGenTextures(1, &id);
}

std::string Texture::ToString(TextureType type)
{
	if (type == TextureType_Diffuse)
		return "Diffuse";
	else if (type == TextureType_Specular)
		return "Specular";
	else if (type == TextureType_Normal)
		return "Normal";
	else if (type == TextureType_Cube)
		return "Cube";
	else if (type == TextureType_TerrainX)
		return "X";
	else if (type == TextureType_TerrainY)
		return "Y";
	else if (type == TextureType_TerrainZ)
		return "Z";
	else
		return "Unknown";
}

void Texture::Bind(int offset)
{
	glActiveTexture(GL_TEXTURE0 + offset);
	glBindTexture(GL_TEXTURE_2D, id);

	if (type != TextureType_Unknown &&  Program::Current() != nullptr)
	{
		string textureName = "texture" + ToString(type);
		Program::Current()->Send(textureName.c_str(), offset);
	}

}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
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

void Texture::Send(GLenum target, GLenum pname, GLint param)
{
	glTexParameteri(target, pname, param);
}

