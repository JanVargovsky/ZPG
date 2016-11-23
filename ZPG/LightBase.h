#pragma once
#include "Updatable.h"
#include "Phong.h"
#include "Transform.h"
#include "Program.h"

#include "glm/vec3.hpp"

class LightBase : public Updatable
{
protected:
	LightBase() = default;

public:
	virtual void Send(Program * program, int index) = 0;
};
