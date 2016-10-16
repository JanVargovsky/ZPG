#include "DependencyResolver.h"

#include "ShaderLoader.h"
#include "CameraFactory.h"
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

DependencyResolver::~DependencyResolver()
{
	// TODO: delete pointers inside container
}

void DependencyResolver::Initialize()
{
	container[typeid(ShaderLoader*)] = new ShaderLoader;
	container[typeid(CameraFactory*)] = new CameraFactory;
	container[typeid(ModelFactory*)] = new ModelFactory;
	container[typeid(ModelManager*)] = new ModelManager(Resolve<ModelFactory*>());
	container[typeid(SceneObjectFactory*)] = new SceneObjectFactory(Resolve<ModelManager*>());
}
