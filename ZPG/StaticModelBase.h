#pragma once
#include "IRenderable.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

#include <boost/optional.hpp>

#include <memory>

class StaticModelBase : public IRenderable
{
protected:
	VBO vbo;
	VAO vao;

	StaticModelBase() = default;

public:
	virtual void PreRender();
	virtual void Render() = 0;
	virtual void PostRender();
};
