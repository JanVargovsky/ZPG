#pragma once
#include "IRenderable.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <assimp/vector3.h>

#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;

	Vertex(glm::vec3 position, glm::vec3 normal)
		: Position(position), Normal(normal)
	{
	}
};

class Mesh : public IRenderable
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	VAO vao;
	VBO vbo;
	EBO ebo;

	//GLuint 
		//VAO,
		//VBO,
		//EBO;

public:
	Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	void Initialize();
};

