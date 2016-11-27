#pragma once
#include "SceneBuilder.h"

class TestSceneBuilder : public SceneBuilder
{
private:
	bool skyBox;
	bool rotate;
public:
	TestSceneBuilder();

	virtual SceneBuilder* BuildObjects(Scene * scene) override;
	virtual SceneBuilder* BuildLights(Scene * scene) override;
	virtual SceneBuilder* BuildSky(Scene * scene) override;
};

