#include "StaticModelBase.h"

void StaticModelBase::PreRender()
{
	vao.Bind();
}

void StaticModelBase::PostRender()
{
	vao.Unbind();
}
