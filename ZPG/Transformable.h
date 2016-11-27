#pragma once
#include "Transform.h"

class Transformable
{
private:
	Transform transform;
protected:
	Transformable() = default;
public:
	Transform & GetTransform();
};
