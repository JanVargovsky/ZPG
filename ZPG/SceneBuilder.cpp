#include "SceneBuilder.h"
#include "DependencyResolver.h"

SceneBuilder::SceneBuilder()
{
	staticModelManager = DependencyResolver::GetInstance().Resolve<StaticModelManager *>();
	modelManager = DependencyResolver::GetInstance().Resolve<ModelManager *>();
}

void SceneBuilder::BuildAll(Scene * scene)
{
	BuildSky(scene);
	BuildObjects(scene);
	BuildLights(scene);
}
