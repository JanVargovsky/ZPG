#include "PointLight.h"

using namespace std;

PointLight::PointLight(glm::vec3 position, Phong phong, float attenuation)
	:LightBase::LightBase(position), phong(phong), attenuation(attenuation)
{
}

void PointLight::Send(Program * program, int index)
{
	string pointsArrayName = "pointLights";
	program->Send((pointsArrayName + "[" + to_string(index) + "].position").c_str(), GetTransform().GetPosition());
	//program->Send((pointsArrayName + "[" + to_string(index) + "].attenuation").c_str(), attenuation);
}