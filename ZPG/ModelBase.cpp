#include "ModelBase.h"

ModelBase::ModelBase()
{
	
}

ModelBase::~ModelBase()
{
}

void ModelBase::PreDraw()
{
	vao.Bind();
}

void ModelBase::Draw()
{
	PreDraw();
	Render();
	PostDraw();
}

void ModelBase::PostDraw()
{
	vao.Bind();
}
