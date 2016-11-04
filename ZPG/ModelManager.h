#pragma once
#include "ManagerBase.h"
#include "StaticModelBase.h"
#include "ModelFactory.h"

typedef ManagerBase<ModelType, StaticModelBase, ModelFactory> ModelManager;
