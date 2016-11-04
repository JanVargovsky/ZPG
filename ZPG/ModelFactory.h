#pragma once
#include "StaticModelBase.h"
#include "FactoryBase.h"

enum ModelType
{
	TriangleModel,
	SquareModel,
	SphereModel,
	SuziFlatModel,
	SuziSmoothModel,
};

class ModelFactory : public FactoryBase<ModelType, StaticModelBase*>
{
public:
	virtual StaticModelBase* Create(ModelType modelType) override;
};
