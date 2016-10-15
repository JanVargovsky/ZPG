#pragma once
#include "ManagerBase.h"
#include "ModelBase.h"
#include "ModelFactory.h"

class ModelManager : public ManagerBase<ModelType, ModelBase, ModelFactory>
{
};

ModelFactory ModelManager::factory;
std::unordered_map<ModelType, std::shared_ptr<ModelBase>> ModelManager::items;
