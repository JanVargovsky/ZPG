#include "ModelBase.h"

void ModelBase::PreRender()
{
	vao.Bind();
}

void ModelBase::PostRender()
{
	vao.Unbind();
}
