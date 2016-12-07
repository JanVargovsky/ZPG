#include <GL/glew.h>
#include "Application.h"

#include <time.h>

#include <vector>
#include <iostream>
#include "BezierCurve.h"
#include "glm/vec2.hpp"

using namespace glm;
using namespace std;

void test()
{
	vector<vec2> points = { vec2(-3,-3),vec2(-1.5, 10), vec2(-1.5,-10), vec2(3,3) };
	BezierCurve curve(points);
	for (double i = 0; i <= 1.; i += 0.1)
	{
		auto p = curve.GetPoint(i);
		cout << p.x << " " << p.y << endl;
	}
}

int main()
{
	test();

	srand(time(0));

	DependencyResolver::GetInstance().Initialize();

	if (!Application::GetInstance().Initialize())
		exit(EXIT_FAILURE);

 	Application::GetInstance().Run();
	return 0;
}
