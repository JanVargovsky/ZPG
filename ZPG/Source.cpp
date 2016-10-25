#include <GL/glew.h>
#include "Application.h"

using namespace std;
using namespace glm;
#include <iostream>

float getAngle(float x, float y)
{
	return atan(x / y);
}

float getDegAngle(float x, float y)
{
	return degrees(atan2(y, x));
}

vec2 getPointFromDegAngle(float deg)
{
	return vec2(
		cos(radians(deg)),
		sin(radians(deg))
	);
}

void test()
{
	float v[] = {
		getDegAngle(1,0),
		getDegAngle(0,1),
		getDegAngle(-1,0),
		getDegAngle(0,-1),
	};

	vec2 p[] = {
		getPointFromDegAngle(v[0]),
		getPointFromDegAngle(v[1]),
		getPointFromDegAngle(v[2]),
		getPointFromDegAngle(v[3]),
	};

	vec3 center = vec3();

	for (float i = 0; i < 360; i+= 45)
	{
		float x = sin(radians(i));
		float y = cos(radians(i));

		float angle = atan(x, y);
		float angleDeg = degrees(angle);
		cout << i << " [" << x << ", " << y << "] " << sqrt(x*x + y*y) << endl;
	}

	for (int i = 0; i <= 360; i += 45)
	{
		float angle = i;
		glm::vec3 p = glm::vec3(
			cos(radians(angle)),
			0,
			sin(radians(angle))
		);

		cout << "angle=" << angle << " => " << p.x << " " << p.z << endl;
	}


}

int main()
{
	//test();
	DependencyResolver::GetInstance().Initialize();

	if (!Application::GetInstance().Initialize())
		exit(EXIT_FAILURE);

 	Application::GetInstance().Run();
	return 0;
}
