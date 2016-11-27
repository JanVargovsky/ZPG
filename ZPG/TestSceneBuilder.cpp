#include "TestSceneBuilder.h"
#include "PointLight.h"
#include "ColorUtils.h"
#include "ErrorChecker.h"
#include "SpotLight.h"
#include "Logger.h"
#include "SkyBox.h"
#include "SkyDome.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

SceneBuilder * TestSceneBuilder::BuildObjects(Scene * scene)
{
	auto program = scene->Add(new Program("Shaders\\Phong.vert", "Shaders\\Phong.frag"));

	{
		auto model = modelManager->Get(ModelType::ModelType_LowPolyTree);
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
		auto obj = scene->Add(new Object(program, modelManager->Get(ModelType::ModelType_FarmHouse)));
		auto &transform = obj->GetTransform();
		transform.SetPosition(vec3(8, 0, 2));
		const float scale = 0.15f;
		transform.SetScale(vec3(scale, scale, scale));
	}
	{
		auto program = scene->Add(new Program("Shaders/Simple.vert", "Shaders/Simple.frag"));
		auto floorObject = scene->Add(new Object(program, staticModelManager->Get(StaticModelType::StaticModelType_Square)));
		floorObject->SetColor(ColorUtils::GetColor(64, 46, 35));
		auto &transform = floorObject->GetTransform();
		transform.SetPosition(vec3(0, 0, 0));
		transform.SetScale(vec3(25));
	}

	return this;
}

SceneBuilder * TestSceneBuilder::BuildLights(Scene * scene)
{
	{
		float a = 4;
		float height = 2;
		auto pointLightPositions = {
			vec3(a, height, a),
			//vec3(a, height, -a),
			//vec3(-a, height, a),
			vec3(-a, height, -a),
		};
		for (auto p : pointLightPositions)
			scene->Add(new PointLight(p, 1));
	}

	{
		// radius change
		auto spotLight = scene->Add(new SpotLight(vec3(0, 3, 0), 1, vec3(0, -1, 0), 0.95f));
		spotLight->RegisterOnUpdate([spotLight]() {
			float r = 0.95f - abs(cos((float)glfwGetTime()) / 3.f);
			//Logger::Information("r=" + to_string(r));
			spotLight->SetRadius(r);
		});

		// direction change
		auto spotLight2 = scene->Add(new SpotLight(vec3(0, 3, 3), 1, vec3(0, -1, 0), 0.93f));
		spotLight2->RegisterOnUpdate([spotLight2]() {
			float x = cos((float)glfwGetTime());
			//Logger::Information("r=" + to_string(r));
			auto dir = spotLight2->GetDirection();
			dir.x = x;
			spotLight2->SetDirection(dir);
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
	bool skyBox = true;
	bool rotate = true;

	Object *sky = nullptr;
	if (skyBox)
	{
		auto program = scene->Add(new Program("Shaders\\SkyBox"));
		string images[6] = {
			"midnight-silence_rt.jpg",
			"midnight-silence_lf.jpg",
			"midnight-silence_up.jpg",
			"midnight-silence_dn.jpg",
			"midnight-silence_bk.jpg",
			"midnight-silence_ft.jpg"
		};

		auto staticSkyBoxModel = staticModelManager->Get(StaticModelType::StaticModelType_Cube);
		auto dynamicSkyBoxModel = modelManager->Get(ModelType::ModelType_SkyBox);

		auto skyBox = sky = scene->Add(new SkyBox(program, dynamicSkyBoxModel, images));
	}
	else
	{
		auto program = scene->Add(new Program("Shaders\\SkyDome"));

		auto dynamicSkyDomeModel = modelManager->Get(ModelType::ModelType_SkyDome);

		auto skyDome = sky = scene->Add(new SkyDome(program, dynamicSkyDomeModel, "SkyDome-Cloud-Few-MidMorning.png", 30));
	}

	if (rotate)
		sky->RegisterOnUpdate([sky]() {
		sky->GetTransform().AddRotation(0.005f, vec3(0, 1, 0));
	});

	return this;
}
