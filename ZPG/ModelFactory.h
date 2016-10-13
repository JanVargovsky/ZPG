#pragma once
#include "ModelBase.h"

#include <memory>

enum ModelType
{
	TriangleModel,
	SquareModel,
	SphereModel,
};

class ModelFactory
{
public:
	std::shared_ptr<ModelBase> Create(ModelType modelType);
};

