#include "DirectionalLight.h"

using namespace std;

DirectionalLight::DirectionalLight(glm::vec3 position, float attenuation, glm::vec3 direction, float angle)
	:PointLight(position, attenuation), direction(direction), angle(angle)
{
}

void DirectionalLight::Send(Program * program, int index)
{
	const string pointsArrayName = "directionLights";
	Send(pointsArrayName, program, index);
}

void DirectionalLight::Send(std::string name, Program * program, int index)
{
	PointLight::Send(name, program, index);

	program->Send((name + "[" + to_string(index) + "].direction").c_str(), direction);
	program->Send((name + "[" + to_string(index) + "].direction").c_str(), angle);
}
