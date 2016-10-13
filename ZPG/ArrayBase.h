#pragma once
#include <GL\glew.h>

enum AttributeType
{
	Float = GL_FLOAT,
};

class ArrayBase
{
private:
	GLuint id;

protected:
	ArrayBase();

public:
	virtual ~ArrayBase();

	void Bind();
	void Unbind();
	void SetAttribute(GLuint layout, GLint size, AttributeType type, GLboolean normalized, GLsizei stride, const void *offset);

private:
	void Generate();
};

