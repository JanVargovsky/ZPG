#include "BezierCurve.h"

#include <cmath>

#include <boost/math/special_functions/binomial.hpp>

BezierCurve::BezierCurve(std::vector<Point> points)
	:points(points)
{
}

Point BezierCurve::GetPoint(float t)
{
	Point result;
	const unsigned int n = points.size();
	for (unsigned int i = 0; i < n; i++)
	{
		auto p = points[i];
		auto b = BernsteinPolynomial(n - 1, i, t);

		result += (p * b);
	}
	return result;
}

float BezierCurve::BernsteinPolynomial(unsigned int n, unsigned int i, float t)
{
	float a = boost::math::binomial_coefficient<float>(n, i);
	float b = pow(t, i);
	float c = pow((1.f - t), n - i);

	return a * b * c;
}
