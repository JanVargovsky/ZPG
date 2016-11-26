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
	case ModelType_StickFigure:
		return "Models\\StickFigure\\Stick_Figure_by_Swp.OBJ";
	case ModelType_Tree:
		return "Models\\Tree\\Tree.obj";
	case ModelType_Butterfly:
		return "Models\\Butterfly\\Butterfly.obj";
	case ModelType_FarmHouse:
		return "Models\\FarmHouse\\Farmhouse OBJ.obj";
	case ModelType_LowPolyTree:
		return "Models\\LowPolyTree\\lowpoyltree.obj";
	case ModelType_SkyBox:
		return "Models\\SkyBox\\skybox.obj";
	case ModelType_SkyDome:
		return "Models\\SkyDome\\skydome.obj";
	default:
		throw exception("Unknown model");
	}
}
