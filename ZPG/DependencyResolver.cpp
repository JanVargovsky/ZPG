#include "DependencyResolver.h"

#include "ShaderLoader.h"
#include "CameraFactory.h"
#include "ModelFactory.h"
#include "SceneObjectFactory.h"
#include "ModelManager.h"
#include "FourSpheresSceneBuilder.h"

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
	Register(new CameraFactory);
	Register(new ModelFactory);
	Register(new ModelManager(Resolve<ModelFactory*>()));
	Register(new SceneObjectFactory(Resolve<ModelManager*>()));

	// CurrentScene
	Register<SceneBuilder>(new FourSpheresSceneBuilder);
}
