#include "DependencyResolver.h"

#include "ShaderLoader.h"
#include "StaticModelFactory.h"
#include "StaticModelManager.h"
#include "FourSpheresSceneBuilder.h"
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
	container.clear();
}

void DependencyResolver::Initialize()
{
	Register(new ShaderLoader);

	Register(new StaticModelFactory);
	Register(new StaticModelManager(Resolve<StaticModelFactory*>()));

	Register(new ModelFactory);
	Register(new ModelManager(Resolve<ModelFactory*>()));

	// CurrentScene
	Register<SceneBuilder>(new FourSpheresSceneBuilder);
}
