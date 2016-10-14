#include "ModelFactory.h"

#include "Triangle.h"
#include "Square.h"
#include "Sphere.h"
#include "SuziFlat.h"

using namespace std;

shared_ptr<ModelBase> ModelFactory::Create(ModelType modelType)
{
	switch (modelType)
	{
	case TriangleModel:
		return shared_ptr<ModelBase>(new Triangle);
	case SquareModel:
		return shared_ptr<ModelBase>(new Square);
	case SphereModel:
		return shared_ptr<ModelBase>(new Sphere);
	case SuziFlatModel:
		return shared_ptr<ModelBase>(new SuziFlat);
	default:
		throw exception("not implemented ModelType");
	}
}
