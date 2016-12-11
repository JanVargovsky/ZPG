#pragma once
#include "LightBase.h"

class DirectionalLight : public LightBase
{
private:
	glm::vec3 direction;
public:
	DirectionalLight(glm::vec3 direction);

	virtual void Send(Program * program, int index = 0) override;

	inline void SetDirection(glm::vec3 value) { direction = value; }
	inline glm::vec3 GetDirection() { return direction; }
};

