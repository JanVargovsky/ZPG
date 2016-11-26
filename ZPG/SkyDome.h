#pragma once
#include "Object.h"
#include "DependencyResolver.h"
#include "TextureLoader.h"

class SkyDome : public Object
{
private:
	Texture* texture;

public:
	SkyDome(Program *program, IRenderable *model, std::string textureName, float radius);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void Initialize(std::string textureName);
};
