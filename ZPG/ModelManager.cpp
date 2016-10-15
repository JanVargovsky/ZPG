#include "ModelManager.h"

using namespace std;

ModelFactory ModelManager::factory;
unordered_map<ModelType, shared_ptr<ModelBase>> ModelManager::items;