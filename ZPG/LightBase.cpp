#include "LightBase.h"

LightBase::LightBase(glm::vec3 position)
{
	transform.SetPosition(position);
}

Transform & LightBase::GetTransform()
{
	return transform;
}
