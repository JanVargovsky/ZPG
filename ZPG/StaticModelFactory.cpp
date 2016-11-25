#include "StaticModelFactory.h"

#include "Triangle.h"
#include "Square.h"
#include "Sphere.h"
#include "SuziFlat.h"
#include "SuziSmooth.h"
#include "Cube.h"

using namespace std;

StaticModelBase* StaticModelFactory::Create(StaticModelType modelType)
{
	StaticModelBase * model;

	switch (modelType)
	{
	case TriangleModel:
		model = new Triangle;
		break;
	case SquareModel:
		model = new Square;
		break;
	case SphereModel:
		model = new Sphere;
		break;
	case SuziFlatModel:
		model = new SuziFlat;
		break;
	case SuziSmoothModel:
		model = new SuziSmooth;
		break;
	case CubeModel:
		model = new Cube;
		break;
	default:
		throw exception("not implemented ModelType");
	}

	return model;
}
