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
	ErrorChecker::CheckOpenGLError();
	auto sphereModel = staticModelManager->Get(SphereModel);
	ErrorChecker::CheckOpenGLError();
	//scene->Add(sphereModel);

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
	ErrorChecker::CheckOpenGLError();

	//auto obj = new Object(program, sphereModel);
	//obj->SetColor(ColorUtils::GetColor(0x80, 0xff, 0x0));
	//scene->Add(obj);

	auto stickFigureModel = modelManager->Get(ModelType::StickFigure);
	ErrorChecker::CheckOpenGLError();
	auto obj = new Object(program, stickFigureModel);
	ErrorChecker::CheckOpenGLError();
	obj->GetTransform().SetPosition(vec3(-3, 0, -3));
	obj->SetColor(vec3(0.5f, 0.5f, 0.5f));
	scene->Add(obj);

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
