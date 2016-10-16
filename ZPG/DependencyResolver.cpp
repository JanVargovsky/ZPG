#include "DependencyResolver.h"

#include "ShaderLoader.h"
#include "ModelFactory.h"
#include "SceneObjectFactory.h"
#include "ModelManager.h"

#include <memory>

using namespace std;

DependencyResolver & DependencyResolver::GetInstance()
{
	static DependencyResolver instance;
	return instance;
}

DependencyResolver::DependencyResolver()
{

}

void DependencyResolver::Register()
{
	container[typeid(ShaderLoader*)] = new ShaderLoader;

	// Factories
	container[typeid(ModelFactory*)] = new ModelFactory;

	// Managers
	container[typeid(ModelManager*)] = new ModelManager(Resolve<ModelFactory*>());
	container[typeid(SceneObjectFactory*)] = new SceneObjectFactory(Resolve<ModelManager*>());
}
