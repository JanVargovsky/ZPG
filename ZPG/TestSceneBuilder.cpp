#include "TestSceneBuilder.h"
#include "PointLight.h"
#include "ColorUtils.h"
#include "ErrorChecker.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

SceneBuilder * TestSceneBuilder::BuildObjects(Scene * scene)
{
	auto program = scene->Add(new Program("Shaders/Phong.vert", "Shaders/Phong.frag"));

	{
		auto obj = scene->Add(new Object(program, modelManager->Get(ModelType::FarmHouse)));
		auto &transform = obj->GetTransform();
		const float scale = 0.2f;
		transform.SetScale(vec3(scale, scale, scale));
	}

	{
		auto program = scene->Add(new Program("Shaders/Simple.vert", "Shaders/Simple.frag"));
		auto floorObject = scene->Add(new Object(program, staticModelManager->Get(StaticModelType::SquareModel)));
		floorObject->SetColor(ColorUtils::GetColor(64,46,35));
		auto &transform = floorObject->GetTransform();
		transform.SetPosition(vec3(0, 0, 0));
		transform.SetScale(vec3(100));
	}

	return this;
}

SceneBuilder * TestSceneBuilder::BuildLights(Scene * scene)
{
	auto pointLight = scene->Add(new PointLight(vec3(5, 5, 5), 1));
	auto pointLight2 = scene->Add(new PointLight(vec3(0, 2, 0), 1));

	return this;
}

SceneBuilder * TestSceneBuilder::BuildSky(Scene * scene)
{
	return this;
}
