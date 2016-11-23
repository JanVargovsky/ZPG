#pragma once
#include "IRenderable.h"
#include "Updatable.h"

class Sky : public IRenderable, public Updatable
{
protected:
	Sky() = default;

public:
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};

