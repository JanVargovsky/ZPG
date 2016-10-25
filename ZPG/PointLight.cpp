#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, Phong phong)
	:LightBase::LightBase(position), phong(phong)
{
}

void PointLight::Send(Program * program)
{
	LightBase::Send(program);
}
