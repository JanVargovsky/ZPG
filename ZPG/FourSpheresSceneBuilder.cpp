#include "FourSpheresSceneBuilder.h"

#include <glm/vec3.hpp>

using namespace glm;

SceneBuilder * FourSpheresSceneBuilder::BuildObjects(Scene * scene)
{
	Program *program = new Program("Shaders/Phong.vert", "Shaders/Phong.frag");
	scene->Add(program);
	auto sphereModel = modelManager->Get(SphereModel);
	scene->Add(sphereModel);

	const float T = 2.f;
	auto positions = {
		// 4
		vec3(T, 0, 0), // right 
		vec3(0, 0, T), // top 
		vec3(-T, 0, 0), // left
		vec3(0, 0, -T), // bottom

		// 8
		//vec3(T, 0, 0), // right 
		//vec3(T, 0, T), // top right
		//vec3(0, 0, T), // top 
		//vec3(-T, 0, T), // top left
		//vec3(-T, 0, 0), // left
		//vec3(-T, 0, -T), // bottom left
		//vec3(0, 0, -T), // bottom
		//vec3(T, 0, -T), // bottom right

		//vec3(0, T, 0), // top
		//vec3(0, -T, 0), // bottom
	};

	bool animate = true;
	float delay = 0;
	for (auto position : positions)
	{
		Object* obj;
		if (animate)
		{
			obj = new Object(program, sphereModel
				, [delay](Object &o) {
				// up and down
				auto position = o.GetTransform().GetPosition();
				position.y = 2 * sin(glfwGetTime() + delay);
				o.GetTransform().SetPosition(position);

				// rotate around
				o.GetTransform().SetAngle(glfwGetTime() * 20 * (delay + 1));
			});
		}
		else
			obj = new Object(program, sphereModel);

		//position.y = delay;
		obj->GetTransform().SetPosition(position);

		scene->Add(obj);
		delay += 1.2f;
	}

	return this;
}

SceneBuilder * FourSpheresSceneBuilder::BuildLights(Scene * scene)
{
	return this;
}
