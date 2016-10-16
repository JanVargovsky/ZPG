#pragma once
#include "ManagerBase.h"
#include "ModelBase.h"
#include "ModelFactory.h"

typedef ManagerBase<ModelType, ModelBase, ModelFactory> ModelManager;

//class ModelManager : public ManagerBase<ModelType, ModelBase, std::shared_ptr<ModelFactory>>
//{
//public:
//	ModelManager(std::shared_ptr<ModelFactory> factory)
//		: ManagerBase(factory)
//	{
//	}
//};