#pragma once
#include <GL\glew.h>

enum BufferType
{
	Vertices = GL_ARRAY_BUFFER,
	Indices = GL_ELEMENT_ARRAY_BUFFER,
};

enum BufferUsage {
	Static = GL_STATIC_DRAW,
	Dynamic = GL_DYNAMIC_DRAW,
};

class BufferBase
{
private:
	GLuint id;
	BufferType bufferType;
	BufferUsage bufferUsage;

protected:
	BufferBase(BufferType type, BufferUsage usage);
public:
	virtual ~BufferBase();

public:
	void Bind();
	void Unbind();

	void BindData(GLsizeiptr size, const void *data);

private:
	void Generate();
};

