#pragma once
#include "FactoryBase.h"
#include "Scene.h"
#include "ModelManager.h"
#include <vector>

enum SceneType
{
	Trash,
	FourBalls,
};

class SceneObjectFactory
{
public:
	std::vector<Object*> GetObjects(SceneType sceneType);

private:
	std::vector<Object*> PrepareTrashScene();
	std::vector<Object*> PrepareFourBallsScene();
};

