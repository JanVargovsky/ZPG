#pragma once
#include "Phong.h"
#include "Transform.h"
#include "Program.h"

#include "glm/vec3.hpp"

class LightBase
{
private:
	Transform transform;

public:
	LightBase(glm::vec3 position);

	virtual void Send(Program * program);

	inline Transform & GetTransform();
};
