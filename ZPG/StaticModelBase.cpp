#include "StaticModelBase.h"
#include "ErrorChecker.h"

void StaticModelBase::PreRender()
{
	vao.Bind();
	ErrorChecker::CheckOpenGLError();
}

void StaticModelBase::PostRender()
{
	vao.Unbind();
	ErrorChecker::CheckOpenGLError();
}
