#include "BufferBase.h"

BufferBase::BufferBase(BufferType type, BufferUsage usage)
	:bufferType(type), bufferUsage(usage)
{
	Generate();
}

BufferBase::~BufferBase()
{
	glDeleteBuffers(1, &id);
}

void BufferBase::Bind()
{
	glBindBuffer(bufferType, id);
}

void BufferBase::Unbind()
{
	glBindBuffer(bufferType, 0);
}

void BufferBase::BindData(const void * data, GLsizeiptr size)
{
	glBufferData(bufferType, size, data, bufferUsage);
}

void BufferBase::Generate()
{
	glGenBuffers(1, &id);
}
