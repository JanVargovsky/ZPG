#pragma once
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

#include <boost/optional.hpp>

#include <memory>

class ModelBase
{
protected:
	VBO vbo;
	VAO vao;
	boost::optional<EBO> ebo;

protected:
	ModelBase();
public:
	~ModelBase();

	void Use();
	void Unuse();
};

