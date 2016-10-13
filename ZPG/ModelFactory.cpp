#include "ModelFactory.h"
#include "Triangle.h"

using namespace std;

shared_ptr<ModelBase> ModelFactory::Create(ModelType modelType)
{
	switch (modelType)
	{
	case TriangleModel:
		return shared_ptr<ModelBase>(new Triangle());
	default:
		throw exception("not implemented ModelType");
	}
}
