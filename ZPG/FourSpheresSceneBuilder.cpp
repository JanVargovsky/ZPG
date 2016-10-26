#include "FourSpheresSceneBuilder.h"
#include "PointLight.h"
#include "ColorUtils.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

SceneBuilder * FourSpheresSceneBuilder::BuildObjects(Scene * scene)
{
	Program *program = new Program("Shaders/Phong.vert", "Shaders/Phong.frag");
	scene->Add(program);
	auto sphereModel = modelManager->Get(SphereModel);
	//auto sphereModel = modelManager->Get(SuziFlatModel);
	scene->Add(sphereModel);

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

	auto obj = new Object(program, sphereModel);
	obj->SetColor(ColorUtils::GetColor(0x80, 0xff, 0x0));
	scene->Add(obj);

	return this;
}

SceneBuilder * FourSpheresSceneBuilder::BuildLights(Scene * scene)
{
	Phong phong = Phong(vec3());
	vec3 position = vec3(0, 2, 0);

	auto pointLight = new PointLight(position, phong);
	//pointLight->RegisterOnUpdate([pointLight]() {
	//	auto & transform = pointLight->GetTransform();
	//	const auto center = vec3(0, 0, 0);
	//	const auto axis = vec3(1, 1, 0);
	//	transform.AddPosition(center, 1, axis);
	//});
	pointLight->Update();
	scene->Add(pointLight);

	return this;
}
