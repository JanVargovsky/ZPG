#include "Terrain.h"
#include "Logger.h"
#include "ErrorChecker.h"

#include <glm/gtc/noise.hpp>

using namespace std;
using namespace glm;


Terrain::Terrain(int w, int h)
	:width(w), height(h)
{
	Initialize();
}

void Terrain::Initialize()
{
	auto arr = Generate(width, height);

	ErrorChecker::CheckOpenGLError();
	vao.Bind();
	{
		vbo.Bind();
		vbo.BindData(arr.data(), arr.size() * sizeof(TerrainVertex));

		// Position
		vao.SetAttribute(0, 3, AttributeType::Float, GL_FALSE, sizeof(TerrainVertex), (GLvoid*)0);
		vao.SetAttribute(1, 3, AttributeType::Float, GL_FALSE, sizeof(TerrainVertex), (GLvoid*)offsetof(TerrainVertex, Normal));

		vbo.Unbind();
	}
	vao.Unbind();
	ErrorChecker::CheckOpenGLError();
}

std::vector<TerrainVertex> Terrain::Generate(int width, int height)
{
	vector<TerrainVertex> result;
	result.reserve(width * height);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			result.push_back(GenerateVertex(x, y));
			result.push_back(GenerateVertex(x, y + 1));
		}

	return result;
}

TerrainVertex Terrain::GenerateVertex(int x, int y)
{
	glm::vec2 c = 4.0f * glm::vec2(x / (float)(width), y / (float)(height));
	auto value = 4 * glm::perlin(c);

	TerrainVertex v;
	v.Position = vec3(-width / 2 + x, value, -height / 2 + y);
	v.Normal = vec3(0, 1, 0);
	return v;
}

void Terrain::Render()
{
	for (int i = 0; i < height; i++)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 2 * i * width, width * 2);
	}
}
