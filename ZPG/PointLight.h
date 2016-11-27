#pragma once
#include "LightBase.h"
#include "IRenderable.h"

class PointLight : public LightBase
{
private:
	glm::vec3 position;
	float attenuation;

public:
	PointLight(glm::vec3 position, float attenuation);

	virtual void Send(Program * program, int index) override;

	inline void SetPosition(glm::vec3 value) { position = value; }
	inline glm::vec3 GetPosition() { return position; }

protected:
	virtual void Send(std::string name, Program * program, int index);
};
