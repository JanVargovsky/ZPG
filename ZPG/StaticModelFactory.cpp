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
	case StaticModelType_Triangle:
		model = new Triangle;
		break;
	case StaticModelType_Square:
		model = new Square;
		break;
	case StaticModelType_Sphere:
		model = new Sphere;
		break;
	case StaticModelType_SuziFlat:
		model = new SuziFlat;
		break;
	case StaticModelType_SuziSmooth:
		model = new SuziSmooth;
		break;
	case StaticModelType_Cube:
		model = new Cube;
		break;
	default:
		throw exception("not implemented StaticModelType");
	}

	return model;
}
