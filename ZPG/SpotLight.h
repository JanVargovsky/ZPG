#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
private:
	glm::vec3 direction;
	float radius;

public:
	SpotLight(glm::vec3 position, float attenuation, glm::vec3 direction, float radius);

	virtual void Send(Program * program, int index) override;

	inline void SetDirection(glm::vec3 value) { direction = glm::normalize(value); }
	inline glm::vec3 GetDirection() { return direction; }

	// Note: Value is based on dot product (cos)
	inline void SetRadius(float value) { radius = value;}
	inline float GetRadius() { return radius; }

protected:
	virtual void Send(std::string name, Program * program, int index) override;
};
