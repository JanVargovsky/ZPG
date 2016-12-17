#include "Terrain.h"
#include "Logger.h"
#include "ErrorChecker.h"
#include "DependencyResolver.h"

#include <glm/gtc/noise.hpp>

using namespace std;
using namespace glm;


Terrain::Terrain(int w, int h)
	:width(w), height(h)
{
	Initialize();
}

Terrain::Terrain(int size)
	: Terrain(size, size)
{
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


	auto textureLoader = DependencyResolver::GetInstance().Resolve<TextureLoader*>();
	string dir = "Models/Terrain";
	//"X.png", "Y.png", "Z.png";
	//"ash.jpg", "snow.jpg", "grass.jpg";
	string textureX = "ash.jpg", textureY = "ash.jpg", textureZ = "ash.jpg";
	x = textureLoader->LoadTexture(dir, textureX, TextureType::TextureType_TerrainX);
	y = textureLoader->LoadTexture(dir, textureY, TextureType::TextureType_TerrainY);
	z = textureLoader->LoadTexture(dir, textureZ, TextureType::TextureType_TerrainZ);
}

std::vector<TerrainVertex> Terrain::Generate(int width, int height)
{
	vector<TerrainVertex> result;
	result.reserve(width * height * 2);

	TerrainVertex *terrain = GenerateTerrain(width, height + 1);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			//result.push_back(GenerateVertex(x, y));
			//result.push_back(GenerateVertex(x, y + 1));
			result.push_back(terrain[y * width + x]);
			result.push_back(terrain[(y + 1) * width + x]);
		}

	return result;
}

TerrainVertex* Terrain::GenerateTerrain(int width, int height)
{
	TerrainVertex *terrain = new TerrainVertex[width * height];

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			glm::vec2 c = 4.0f * glm::vec2(x / (float)(width), y / (float)(height));
			auto value = 2 * glm::perlin(c);
			terrain[y * width + x].Position = vec3(-width / 2 + x, value, -height / 2 + y);
		}


	for (int y = 1; y < height - 1; y++)
		for (int x = 1; x < width - 1; x++)
		{
			// points
			//vec2 pL = vec2(x - 1, y);
			//vec2 pR = vec2(x + 1, y);
			//vec2 pD = vec2(x, y - 1);
			//vec2 pU = vec2(x, y + 1);

			//float hL = terrain[y * height + x - 1].Position.y;
			//float hR = terrain[y * height + x + 1].Position.y;
			//float hD = terrain[(y + 1) * height + x].Position.y;
			//float hU = terrain[(y - 1) * height + x].Position.y;

			// //deduce terrain normal
			//terrain[y * width + x].Normal = normalize(vec3(hL - hR, hD - hU, 2.f));


			vec3 mid = terrain[y * height + x].Position;

			vec3 v1 = normalize(terrain[y * height + x + 1].Position - mid); // left
			vec3 v2 = normalize(terrain[(y - 1) * height + x].Position - mid); // down
			vec3 v3 = normalize(terrain[y * height + x - 1].Position - mid); // right
			vec3 v4 = normalize(terrain[(y + 1) * height + x].Position - mid); // up

			vec3 v12 = normalize(cross(v1, v2));
			vec3 v23 = normalize(cross(v2, v3));
			vec3 v34 = normalize(cross(v3, v4));
			vec3 v41 = normalize(cross(v4, v1));

			terrain[y * width + x].Normal = normalize(v12 + v23 + v34 + v41);
		}

	return terrain;
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
	x->Bind(0);
	y->Bind(1);
	z->Bind(2);

	for (int i = 0; i < height; i++)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 2 * i * width, width * 2);
	}
}
