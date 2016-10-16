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

class SceneObjectFactory : public FactoryBase<SceneType, std::vector<Object*>>
{
public:
	std::vector<Object*> Create(SceneType sceneType) override;

private:
	std::vector<Object*> PrepareTrashScene();
	std::vector<Object*> PrepareFourBallsScene();
};

