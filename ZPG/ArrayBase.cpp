#include "ArrayBase.h"

ArrayBase::ArrayBase()
{
	Generate();
}

ArrayBase::~ArrayBase()
{
	glDeleteVertexArrays(1, &id);
}

void ArrayBase::Bind()
{
	glBindVertexArray(id);
}

void ArrayBase::Unbind()
{
	glBindVertexArray(0);
}

void ArrayBase::SetAttribute(GLuint layout, GLint size, AttributeType type, GLboolean normalized, GLsizei stride, const void * offset)
{
	glVertexAttribPointer(layout, size, type, normalized, stride, offset);
	glEnableVertexAttribArray(layout);
}

void ArrayBase::Generate()
{
	glGenVertexArrays(1, &id);
}
