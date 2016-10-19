#pragma once
#include "ModelBase.h"
#include "FactoryBase.h"

enum ModelType
{
	TriangleModel,
	SquareModel,
	SphereModel,
	SuziFlatModel,
	SuziSmoothModel,
};

class ModelFactory : public FactoryBase<ModelType, ModelBase*>
{
public:
	virtual ModelBase* Create(ModelType modelType) override;
};
