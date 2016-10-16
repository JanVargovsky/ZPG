#pragma once
#include "FactoryBase.h"
#include "Object.h"

enum ObjectType
{
	TriangleObject,
	SquareObject,
	SphereObject,
	SuziFlatObject,
	SuziSmoothObject,
};

class ObjectFactory : public FactoryBase<ObjectType, Object*>
{
public:
	virtual Object* Create(ObjectType key) override;
};

