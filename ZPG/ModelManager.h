#pragma once
#include "ManagerBase.h"
#include "ModelBase.h"
#include "ModelFactory.h"

class ModelManager : public ManagerBase<ModelType, ModelBase, ModelFactory>
{
};
