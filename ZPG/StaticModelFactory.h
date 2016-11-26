#pragma once
#include "StaticModelBase.h"
#include "FactoryBase.h"

enum StaticModelType
{
	StaticModelType_Triangle,
	StaticModelType_Square,
	StaticModelType_Sphere,
	StaticModelType_SuziFlat,
	StaticModelType_SuziSmooth,
	StaticModelType_Cube,
};

class StaticModelFactory : public FactoryBase<StaticModelType, StaticModelBase*>
{
public:
	virtual StaticModelBase* Create(StaticModelType modelType) override;
};
