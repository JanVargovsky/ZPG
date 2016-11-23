#pragma once
#include "Sky.h"
#include "TextureLoader.h";

class SkyBox : public Sky
{
private:
	Texture textures[6];

public:
	SkyBox(std::string image);
	SkyBox(std::string images[6]);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
};

