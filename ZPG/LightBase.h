#pragma once
#include "Phong.h"

#include "glm/vec3.hpp"
#include "Program.h"

class LightBase
{
private:
	glm::vec3 position;

public:
	LightBase(glm::vec3 position);

	virtual void Send(Program * program);

	inline glm::vec3 GetPosition();
	inline void SetPosition(glm::vec3 value);
};
