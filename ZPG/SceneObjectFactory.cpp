#include "SceneObjectFactory.h"
#include "DependencyResolver.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;


SceneObjectFactory::SceneObjectFactory(ModelManager * modelManager)
	:modelManager(modelManager)
{
}

vector<Object*> SceneObjectFactory::Create(SceneType sceneType)
{
	switch (sceneType)
	{
	case Trash:
		return PrepareTrashScene();
	case FourBalls:
		return PrepareFourBallsScene();
	default:
		throw exception("Not implemented scene");
	}
}

vector<Object*> SceneObjectFactory::PrepareTrashScene()
{
	vector<Object*> result;

	shared_ptr<Program> program = make_shared<Program>("Shaders/Simple.vert", "Shaders/Simple.frag");

	auto triangleModel = modelManager->Get(TriangleModel);
	auto squareModel = modelManager->Get(SquareModel);
	auto sphereModel = modelManager->Get(SphereModel);
	auto suziFlatModel = modelManager->Get(SuziFlatModel);
	auto suziSmoothModel = modelManager->Get(SuziSmoothModel);

	result.push_back(new Object(program, squareModel));

	auto sphereObject = new Object(program, sphereModel, [](Object &o) {o.GetTransform().SetAngle(glfwGetTime() * 50.f); });
	sphereObject->GetTransform().SetPosition(vec3(3, 0, 3));
	result.push_back(sphereObject);

	auto suziFlatObject = new Object(program, suziFlatModel, [](Object &o) {o.GetTransform().SetAngle(glfwGetTime() * 50.f); });
	suziFlatObject->GetTransform().SetPosition(vec3(0, 3, 3));
	result.push_back(suziFlatObject);

	auto suziSmoothObject = new Object(program, suziSmoothModel, [](Object &o) {o.GetTransform().SetAngle(glfwGetTime() * -50.f); });
	suziSmoothObject->GetTransform().SetPosition(vec3(3, 3, 0));
	result.push_back(suziSmoothObject);

	vec3 axis[3] = { vec3(0,0,1),vec3(0,1,0), vec3(1,0,0) };
	float x = -1.5f;
	for (size_t i = 0; i < 3; i++)
	{
		auto scaleObject = new Object(program, triangleModel, [i](Object & o)
		{
			o.GetTransform().SetScale(abs(sin(glfwGetTime() + i)) / 3 + 0.1f);
		});
		scaleObject->GetTransform().SetPosition(vec3(x, 1.3, 0));
		result.push_back(scaleObject);

		auto angleObject = new Object(program, triangleModel, [](Object & o)
		{
			o.GetTransform().SetAngle(glfwGetTime() * 50.f);
		});
		angleObject->GetTransform().SetPosition(vec3(x, 0, 0));
		angleObject->GetTransform().SetScale(0.5f);
		angleObject->GetTransform().SetAxis(axis[i]);
		result.push_back(angleObject);

		auto positionObject = new Object(program, triangleModel, [i](Object & o)
		{
			o.GetTransform().SetPosition(vec3(sin(glfwGetTime()) + i - 1, -1.3, 0));
			o.GetTransform().SetScale(abs(sin(glfwGetTime() + i)) / 3 + 0.1f);
			o.GetTransform().SetAngle((glfwGetTime() + i) * 50.f);

		});
		positionObject->GetTransform().SetAxis(axis[i]);
		result.push_back(positionObject);

		x += 1.5f;
	}

	return result;
}

vector<Object*> SceneObjectFactory::PrepareFourBallsScene()
{
	vector<Object*> result;

	auto program = make_shared<Program>("Shaders/Lambert.vert", "Shaders/Lambert.frag");

	auto sphereModel = modelManager->Get(SphereModel);

	const float T = 1.5f;
	auto positions = {
		vec3(T, 0, T),
		vec3(-T, 0, T),
		vec3(T, 0, -T),
		vec3(-T, 0, -T),
		vec3(0, -T, 0)
	};

	for (auto position : positions)
	{
		auto obj = new Object(program, sphereModel);
		obj->GetTransform().SetPosition(position);
		result.push_back(obj);
	}

	return result;
}