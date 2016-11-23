#pragma once
#include "FactoryBase.h"
#include "Model.h"

enum ModelType {
	StickFigure,
	Tree,
	Butterfly,
	FarmHouse,
	LowPolyTree
};

class ModelFactory : public FactoryBase<ModelType, Model*> 
{
public:
	virtual Model* Create(ModelType modelType) override;
private:
	std::string GetPath(ModelType modelType);
};
