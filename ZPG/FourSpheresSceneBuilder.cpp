#include "FourSpheresSceneBuilder.h"
#include "PointLight.h"
#include "ColorUtils.h"
#include "ErrorChecker.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

SceneBuilder * FourSpheresSceneBuilder::BuildObjects(Scene * scene)
{
	Program *program = new Program("Shaders/Phong.vert", "Shaders/Phong.frag");
	scene->Add(program);
	auto sphereModel = staticModelManager->Get(SphereModel);

	const float T = 2.f;
	auto positions = {
		// 4
		//vec3(T, 0, 0), // right 
		//vec3(0, 0, T), // top 
		//vec3(-T, 0, 0), // left
		//vec3(0, 0, -T), // bottom

		// 8
		vec3(T, 0, 0), // right 
		vec3(T, 0, T), // top right
		vec3(0, 0, T), // top 
		vec3(-T, 0, T), // top left
		vec3(-T, 0, 0), // left
		vec3(-T, 0, -T), // bottom left
		vec3(0, 0, -T), // bottom
		vec3(T, 0, -T), // bottom right

		//vec3(0, T, 0), // top
		//vec3(0, -T, 0), // bottom
	};

	bool animate = true;
	for (auto position : positions)
	{
		auto obj = new Object(program, sphereModel);
		if (animate)
			obj->RegisterOnUpdate([obj]() {
			auto &transform = obj->GetTransform();
			const vec3 axis = vec3(0, 0, 1);
			const vec3 center = vec3(3, 0, 2);
			const float angle = 1;
			transform.AddPosition(center, angle, axis);
		});

		obj->SetColor(ColorUtils::GetColor(0x7f, 0x2f, 0xff));
		obj->Update();

		auto &transform = obj->GetTransform();
		transform.SetPosition(position);

		scene->Add(obj);
	}

	auto stickFigureModel = modelManager->Get(ModelType::StickFigure);
	auto obj = new Object(program, stickFigureModel);
	obj->GetTransform().SetPosition(vec3(-3, 4, -3));
	obj->GetTransform().SetScale(vec3(2));
	obj->SetColor(vec3(0.5f, 0.5f, 0.5f));
	scene->Add(obj);

	auto floorObject = new Object(program, staticModelManager->Get(StaticModelType::SquareModel));
	floorObject->SetColor(ColorUtils::GetRandomColor());
	auto &transform = floorObject->GetTransform();
	transform.SetPosition(vec3(0, 0, 0));
	transform.SetScale(vec3(100));
	scene->Add(floorObject);


	auto treeModel = modelManager->Get(ModelType::Tree);
	for (int x = -20; x <= 20; x += 5)
		for (int z = -20; z <= 20; z += 5)
		{
			auto tree = new Object(program, treeModel);
			float angle = ((float)(rand() % 30) / 10) + 1;
			if (rand() % 2 == 0)
				angle *= -1;
			tree->RegisterOnUpdate([tree, angle]() {
				tree->GetTransform().AddRotation(angle, vec3(0, 1, 0));
			});
			tree->SetColor(ColorUtils::GetRandomColor());
			auto &t = tree->GetTransform();
			t.SetPosition(vec3(x, 0, z));
			scene->Add(tree);
		}

	return this;
}

SceneBuilder * FourSpheresSceneBuilder::BuildLights(Scene * scene)
{
	auto pointLight = new PointLight(vec3(5, 5, 5), Phong(vec3()), 1);
	//pointLight->RegisterOnUpdate([pointLight]() {
	//	auto & transform = pointLight->GetTransform();
	//	const auto center = vec3(0, 0, 0);
	//	const auto axis = vec3(0, 1, 0);
	//	transform.AddPosition(center, 4, axis);
	//});
	//pointLight->Update();
	scene->Add(pointLight);

	auto pointLight2 = new PointLight(vec3(0, 2, 0), Phong(vec3()), 1);
	scene->Add(pointLight2);

	return this;
}
