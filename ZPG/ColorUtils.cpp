#include "ColorUtils.h"

using namespace glm;

glm::vec3 ColorUtils::GetColor(int r, int g, int b)
{
	return vec3(
		r / 255.f,
		g / 255.f,
		b / 255.f
	);
}
