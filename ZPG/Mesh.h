#pragma once
#include "Mesh.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <glm/vec3.hpp>
#include <GL\glew.h>

#include <vector>

class Mesh
{
private:
	struct Vertex {
		glm::vec3 Position, Normal;
	};

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	VAO vao;
	VBO vbo;
	EBO ebo;
public:
	Mesh();
	~Mesh();
};

