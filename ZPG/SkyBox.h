#pragma once
#include "Object.h"
#include "Program.h"

class SkyBox : public Object
{
private:
	GLuint textureId;

public:
	SkyBox(Program *program, StaticModelBase *staticModel, std::string images[6]);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void Initialize(std::string images[6]);
};

