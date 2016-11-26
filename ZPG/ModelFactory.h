#pragma once
#include "FactoryBase.h"
#include "Model.h"

enum ModelType {
	ModelType_StickFigure,
	ModelType_Tree,
	ModelType_Butterfly,
	ModelType_FarmHouse,
	ModelType_LowPolyTree,
	ModelType_SkyBox,
	ModelType_SkyDome,
};

class ModelFactory : public FactoryBase<ModelType, Model*> 
{
public:
	virtual Model* Create(ModelType modelType) override;
private:
	std::string GetPath(ModelType modelType);
};
