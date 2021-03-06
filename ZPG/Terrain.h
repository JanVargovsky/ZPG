#pragma once
#include "StaticModelBase.h"
#include "Texture.h"
#include "TextureLoader.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <vector>

struct TerrainVertex {
	glm::vec3 Position;
	glm::vec3 Normal = glm::vec3(0,1,0);
};

class Terrain : public StaticModelBase
{
private:
	int width, height;
	Texture *textureLow, *textureNormal, *textureHigh;

public:
	Terrain(int w, int h);
	Terrain(int size);

private:
	void Initialize();
	std::vector<TerrainVertex> GenerateTriangleStripData(int width, int height);
	std::vector<TerrainVertex> GenerateTerrain(int width, int height);
	TerrainVertex GenerateVertex(int x, int y);

public:
	virtual void Render();
};

