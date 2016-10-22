#pragma once
#include "LightBase.h"

class PointLight : public LightBase
{
private:
	const Phong phong;

public:
	PointLight(glm::vec3 position, Phong phong);
};
