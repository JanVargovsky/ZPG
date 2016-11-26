#pragma once
#include "Sky.h"
#include "TextureLoader.h";

class SkyDome : public Sky
{
private:
	GLuint textureId;

public:
	SkyDome( std::string paths);
};
