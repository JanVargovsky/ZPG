#include "TestSceneBuilder.h"
#include "PointLight.h"
#include "ColorUtils.h"
#include "ErrorChecker.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

SceneBuilder * TestSceneBuilder::BuildObjects(Scene * scene)
{
	Program *program = new Program("Shaders/Phong.vert", "Shaders/Phong.frag");
	scene->Add(program);


	auto butterflyModel = modelManager->Get(ModelType::Butterfly);
	{
		auto butterflyObject = new Object(program, butterflyModel);
		auto &transform = butterflyObject->GetTransform();
		butterflyObject->RegisterOnUpdate([&transform]() {
			//transform.AddRotation(2, vec3(0, 1, 0));
		});
		const float scale = 0.2f;
		transform.SetScale(vec3(scale, scale, scale));
		transform.SetPosition(vec3(-15, 0, 15));
		scene->Add(butterflyObject);
	}

	{
		Program *program = new Program("Shaders/Simple.vert", "Shaders/Simple.frag");
		scene->Add(program);
		auto floorObject = new Object(program, staticModelManager->Get(StaticModelType::SquareModel));
		floorObject->SetColor(ColorUtils::GetRandomColor());
		auto &transform = floorObject->GetTransform();
		transform.SetPosition(vec3(0, 0, 0));
		transform.SetScale(vec3(100));
		scene->Add(floorObject);
	}

	return this;
}

SceneBuilder * TestSceneBuilder::BuildLights(Scene * scene)
{
	auto pointLight = new PointLight(vec3(5, 5, 5), 1);
	scene->Add(pointLight);

	auto pointLight2 = new PointLight(vec3(0, 2, 0), 1);
	scene->Add(pointLight2);

	return this;
}
