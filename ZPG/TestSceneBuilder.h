#pragma once
#include "SceneBuilder.h"

class TestSceneBuilder : public SceneBuilder
{
public:
	virtual SceneBuilder* BuildObjects(Scene * scene) override;
	virtual SceneBuilder* BuildLights(Scene * scene) override;
};

