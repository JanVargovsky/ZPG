#pragma once
#include "Scene.h"
#include "ModelManager.h"

class SceneBuilder
{
protected:
	SceneBuilder();
	ModelManager *modelManager;

public:
	virtual SceneBuilder* BuildObjects(Scene * scene) = 0;
	virtual SceneBuilder* BuildLights(Scene * scene) = 0;
};
