#include "LightBase.h"

LightBase::LightBase(glm::vec3 position)
{
	transform.SetPosition(position);
}

void LightBase::Send(Program * program)
{
	program->Send("lightPosition", transform.GetPosition());
}

Transform & LightBase::GetTransform()
{
	return transform;
}
