#pragma once
#include "ModelBase.h"

#include <memory>

enum ModelType
{
	TriangleModel,
	SquareModel,
	SphereModel,
	SuziFlatModel,
	SuziSmoothModel,
};

class ModelFactory
{
public:
	std::shared_ptr<ModelBase> Create(ModelType modelType);
};

