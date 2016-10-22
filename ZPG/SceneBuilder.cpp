#include "SceneBuilder.h"

#include "DependencyResolver.h"

SceneBuilder::SceneBuilder()
{
	modelManager = DependencyResolver::GetInstance().Resolve<ModelManager *>();
}
