#include "ModelBase.h"



ModelBase::ModelBase()
{
	
}


ModelBase::~ModelBase()
{
}

void ModelBase::Use()
{
	vao.Bind();
}

void ModelBase::Unuse()
{
	vao.Unbind();
}
