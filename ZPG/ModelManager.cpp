#include "ModelManager.h"

#include "Triangle.h"

using namespace std;

ModelFactory ModelManager::modelFactory;
unordered_map<ModelType, shared_ptr<ModelBase>> ModelManager::models;

shared_ptr<ModelBase> ModelManager::Get(ModelType modelType)
{
	shared_ptr<ModelBase> result;
	auto modelIt = models.find(modelType);
	if (modelIt == models.end())
	{
		result = modelFactory.Create(modelType);
		models.insert({modelType, result});
	}
	else
		result = modelIt->second;


	return result;
}
