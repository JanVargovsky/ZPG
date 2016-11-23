#pragma once
#include "PointLight.h"

class DirectionalLight : public PointLight
{
private:
	glm::vec3 direction;
	float angle;

public:
	DirectionalLight(glm::vec3 position, float attenuation, glm::vec3 direction, float angle);

	virtual void Send(Program * program, int index) override;

protected:
	virtual void Send(std::string name, Program * program, int index) override;
};
