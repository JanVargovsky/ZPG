#pragma once
#include "ModelBase.h"
#include "FactoryBase.h"

#include <memory>

enum ModelType
{
	TriangleModel,
	SquareModel,
	SphereModel,
	SuziFlatModel,
	SuziSmoothModel,
};

class ModelFactory : public FactoryBase<ModelType, std::shared_ptr<ModelBase>>
{
public:
	std::shared_ptr<ModelBase> Create(ModelType modelType) override;
};

