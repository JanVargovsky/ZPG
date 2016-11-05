#include "SceneBuilder.h"
#include "DependencyResolver.h"

SceneBuilder::SceneBuilder()
{
	staticModelManager = DependencyResolver::GetInstance().Resolve<StaticModelManager *>();
	modelManager = DependencyResolver::GetInstance().Resolve<ModelManager *>();
}
