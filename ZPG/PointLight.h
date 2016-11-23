#pragma once
#include "LightBase.h"

class PointLight : public LightBase
{
private:
	float attenuation;

public:
	PointLight(glm::vec3 position, float attenuation);

	virtual void Send(Program * program, int index) override;

protected:
	virtual void Send(std::string name, Program * program, int index);
};
