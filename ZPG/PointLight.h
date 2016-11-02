#pragma once
#include "LightBase.h"

class PointLight : public LightBase
{
private:
	const Phong phong;
	float attenuation;

public:
	PointLight(glm::vec3 position, Phong phong, float attenuation);

	virtual void Send(Program * program, int index) override;
};
