#include "SpotLight.h"

using namespace std;

SpotLight::SpotLight(glm::vec3 position, float attenuation, glm::vec3 direction, float radius)
	:PointLight(position, attenuation), direction(direction), radius(radius)
{
}

void SpotLight::Send(Program * program, int index)
{
	const string pointsArrayName = "spotLights";
	Send(pointsArrayName, program, index);
}

void SpotLight::Send(std::string name, Program * program, int index)
{
	PointLight::Send(name, program, index);

	program->Send((name + "[" + to_string(index) + "].direction").c_str(), direction);
	program->Send((name + "[" + to_string(index) + "].radius").c_str(), radius);
}
