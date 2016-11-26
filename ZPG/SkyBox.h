#pragma once
#include "Object.h"
#include "Program.h"

class SkyBox : public Object
{
private:
	GLuint textureId;

public:
	SkyBox(Program *program, IRenderable *model, std::string paths[6]);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void Initialize(std::string textures[6]);
};
