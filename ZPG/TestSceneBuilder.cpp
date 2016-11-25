#include "TestSceneBuilder.h"
#include "PointLight.h"
#include "ColorUtils.h"
#include "ErrorChecker.h"
#include "SpotLight.h"
#include "Logger.h"
#include "SkyBox.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

SceneBuilder * TestSceneBuilder::BuildObjects(Scene * scene)
{
	auto program = scene->Add(new Program("Shaders/Phong.vert", "Shaders/Phong.frag"));

	{
		auto model = modelManager->Get(ModelType::LowPolyTree);
		const float X = 4;
		for (float x = -X; x <= X; x += 1)
			for (float z = -X; z <= X; z += 1)
			{
				auto &t = scene->Add(new Object(program, model))->GetTransform();
				t.SetPosition(vec3(x, 0, z));
				t.SetScale(vec3(0.5, 0.5, 0.5));
			}
	}

	{
		auto obj = scene->Add(new Object(program, modelManager->Get(ModelType::FarmHouse)));
		auto &transform = obj->GetTransform();
		transform.SetPosition(vec3(10, 0, 10));
		const float scale = 0.15f;
		transform.SetScale(vec3(scale, scale, scale));
	}
	{
		//auto program = scene->Add(new Program("Shaders/Simple.vert", "Shaders/Simple.frag"));
		//auto floorObject = scene->Add(new Object(program, staticModelManager->Get(StaticModelType::SquareModel)));
		//floorObject->SetColor(ColorUtils::GetColor(64, 46, 35));
		//auto &transform = floorObject->GetTransform();
		//transform.SetPosition(vec3(0, 0, 0));
		//transform.SetScale(vec3(100));
	}

	return this;
}

SceneBuilder * TestSceneBuilder::BuildLights(Scene * scene)
{
	//auto pointLight = scene->Add(new PointLight(vec3(5, 5, 5), 1));
	//auto pointLight2 = scene->Add(new PointLight(vec3(0, 2, 0), 1));

	{
		auto spotLight = scene->Add(new SpotLight(vec3(0, 3, 0), 1, vec3(0, -1, 0), 0.90));
		spotLight->RegisterOnUpdate([spotLight]() {
			auto r = 0.9f - abs(cos(glfwGetTime()) / 3);
			Logger::Information("r=" + to_string(r));
			spotLight->SetRadius(r);
		});
		//spotLight->RegisterOnUpdate([spotLight]() {
		//	//float radius = abs(sin(glfwGetTime()));
		//	//spotLight->SetRadius(radius);

		//	//float x = 3 + sin(glfwGetTime());
		//	//Logger::Information("x= " + to_string(x));
		//	//spotLight->SetPosition(vec3(0, x, 0));

		//	float r = abs(sin(glfwGetTime()));
		//	Logger::Information("r= " + to_string(r));
		//	spotLight->SetRadius(r);
		//});
	}
	return this;
}

SceneBuilder * TestSceneBuilder::BuildSky(Scene * scene)
{
	auto program = scene->Add(new Program("Shaders/SkyBox"));
	string images[6] = {
		"Models/mp_midnight/midnight-silence_rt.jpg",
		"Models/mp_midnight/midnight-silence_lf.jpg",
		"Models/mp_midnight/midnight-silence_up.jpg",
		"Models/mp_midnight/midnight-silence_dn.jpg",
		"Models/mp_midnight/midnight-silence_bk.jpg",
		"Models/mp_midnight/midnight-silence_ft.jpg"
	};

	auto skyBox = new SkyBox(program, staticModelManager->Get(StaticModelType::CubeModel), images);
	scene->Add(skyBox);

	return this;
}
