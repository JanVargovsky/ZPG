#pragma once
#include "FactoryBase.h"
#include "Object.h"

#include <memory>

enum ObjectType
{
	TriangleObject,
	SquareObject,
	SphereObject,
	SuziFlatObject,
	SuziSmoothObject,
};

class ObjectFactory : public FactoryBase<ObjectType, std::shared_ptr<Object>>
{
public:
	virtual std::shared_ptr<Object> Create(ObjectType key) override;
};

