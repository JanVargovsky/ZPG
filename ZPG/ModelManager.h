#pragma once
#include "ModelBase.h"
#include "ModelFactory.h"

#include <unordered_map>

class ModelManager
{
private:
	static std::unordered_map<ModelType, std::shared_ptr<ModelBase>> models;
	static ModelFactory modelFactory;
public:
	static std::shared_ptr<ModelBase> Get(ModelType modelType);

};

