#pragma once

#include "glm/vec2.hpp"

#include <vector>

typedef glm::vec2 Point;

class BezierCurve
{
private:
	std::vector<Point> points;

public:
	BezierCurve(std::vector<Point> points);

	Point GetPoint(float t);

private:
	float BernsteinPolynomial(unsigned int n, unsigned int i, float t);
};