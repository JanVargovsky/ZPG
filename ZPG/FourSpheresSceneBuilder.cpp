#include "FourSpheresSceneBuilder.h"
#include "PointLight.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

SceneBuilder * FourSpheresSceneBuilder::BuildObjects(Scene * scene)
{
	Program *program = new Program("Shaders/Phong.vert", "Shaders/Phong.frag");
	scene->Add(program);
	//auto sphereModel = modelManager->Get(SphereModel);
	auto sphereModel = modelManager->Get(SuziFlatModel);
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
				auto &transform = o.GetTransform();
				//auto position = transform.GetPosition();
				//position.y = 2 * sin(glfwGetTime() + delay);
				//o.GetTransform().SetPosition(position);

				//vec3 vecToCenter = cross(vec3() - transform.GetPosition(), vec3(0, 1, 0));
				//transform.AddRotation(1, vecToCenter);
				const vec3 axis = vec3(0, 1, 0);
				const vec3 center = vec3(0, 0, 0);
				const float angle = 0.3f;
				transform.AddPosition(center, angle, axis);
				transform.AddRotation(angle, axis);
			});
		}
		else
			obj = new Object(program, sphereModel);

		auto &transform = obj->GetTransform();
		transform.SetPosition(position);
		vec3 vecToCenter = cross(vec3() - transform.GetPosition(), vec3(0, 1, 0));

		scene->Add(obj);
		delay += 1.2f;
	}

	return this;
}

SceneBuilder * FourSpheresSceneBuilder::BuildLights(Scene * scene)
{
	Phong phong = Phong(vec3());
	vec3 position = vec3(0,0,0);

	scene->Add(new PointLight(position, phong));

	//position = vec3(5, 0, 5);
	//scene->Add(new PointLight(position, phong));

	return this;
}
