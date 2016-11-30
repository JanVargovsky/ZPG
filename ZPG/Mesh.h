#pragma once
#include "IRenderable.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <assimp/vector3.h>

#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 textureCoords, glm::vec3 tangent, glm::vec3 bitangent)
		: Position(position), Normal(normal), TextureCoords(textureCoords), Tangent(tangent), Bitangent(bitangent)
	{
	}
};

class Mesh : public IRenderable
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture*> textures;

	VAO vao;
	VBO vbo;
	EBO ebo;

public:
	Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture*> &textures);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	void Initialize();
};

