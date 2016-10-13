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

	virtual void Render() = 0;
public:
	~ModelBase();

	virtual void PreDraw();
	void Draw();
	virtual void PostDraw();
};

