#include "ModelFactory.h"

using namespace std;

Model * ModelFactory::Create(ModelType modelType)
{
	string path = GetPath(modelType);
	Model *model = new Model(path);
	return model;
}

std::string ModelFactory::GetPath(ModelType modelType)
{
	switch (modelType)
	{
	case StickFigure:
		return "Models/StickFigure/Stick_Figure_by_Swp.OBJ";
	case Tree:
		return "Models/Tree/Tree.obj";
	case Butterfly:
		return "Models/Butterfly/Butterfly.obj";
	case FarmHouse:
		return "Models/FarmHouse/Farmhouse OBJ.obj";
	default:
		throw exception("Unknown model");
	}
}
