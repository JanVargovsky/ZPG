#pragma once
#include "Object.h"

class SkyBox : public Object
{
private:
	GLuint textureId;

public:
	SkyBox(Program *program, IRenderable *model, std::string names[6]);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void Initialize(std::string names[6]);
};
