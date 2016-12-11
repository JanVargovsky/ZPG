#include "DirectionalLight.h"

using namespace std;

DirectionalLight::DirectionalLight(glm::vec3 direction)
	:direction(direction)
{
}

void DirectionalLight::Send(Program * program, int index)
{
	const string uniformLightName = "directionalLight";

	program->Send((uniformLightName + ".direction").c_str(), direction);
}
