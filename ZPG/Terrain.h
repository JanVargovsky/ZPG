#pragma once
#include "StaticModelBase.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <vector>

struct TerrainVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
};

class Terrain : public StaticModelBase
{
private:
	int width, height;

public:
	Terrain(int w, int h);

private:
	void Initialize();
	std::vector<TerrainVertex> Generate(int width, int height);
	TerrainVertex GenerateVertex(int x, int y);

	virtual void Render();
};

