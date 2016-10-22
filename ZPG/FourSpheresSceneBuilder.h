#pragma once
#include "SceneBuilder.h"

class FourSpheresSceneBuilder : public SceneBuilder
{
public:
	virtual SceneBuilder* BuildObjects(Scene * scene) override;
	virtual SceneBuilder* BuildLights(Scene * scene) override;
};
