#pragma once
#include "StaticModelBase.h"
#include "FactoryBase.h"

enum StaticModelType
{
	TriangleModel,
	SquareModel,
	SphereModel,
	SuziFlatModel,
	SuziSmoothModel,
};

class StaticModelFactory : public FactoryBase<StaticModelType, StaticModelBase*>
{
public:
	virtual StaticModelBase* Create(StaticModelType modelType) override;
};