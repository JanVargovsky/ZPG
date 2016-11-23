#include "PointLight.h"

using namespace std;

PointLight::PointLight(glm::vec3 position, float attenuation)
	: position(position), attenuation(attenuation)
{
}

void PointLight::Send(Program * program, int index)
{
	const string pointsArrayName = "pointLights";
	Send(pointsArrayName, program, index);
}

void PointLight::Send(std::string name, Program * program, int index)
{
	program->Send((name + "[" + to_string(index) + "].position").c_str(), position);
	program->Send((name + "[" + to_string(index) + "].attenuation").c_str(), attenuation);
}
