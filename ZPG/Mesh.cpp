#include "Mesh.h"
#include "ErrorChecker.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture*> &textures)
	:vertices(vertices), indices(indices), textures(textures)
{
	Initialize();
}

void Mesh::PreRender()
{
	vao.Bind();

	for (auto texture : textures)
		texture->Bind();

	//glBindVertexArray(this->VAO);
}

void Mesh::Render()
{
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::PostRender()
{
	vao.Unbind();

	for (auto texture : textures)
		texture->Unbind();

	//glBindVertexArray(0);
}

void Mesh::Initialize()
{
	//ErrorChecker::CheckOpenGLError();
	//// Create buffers/arrays
	////glGenBuffers(1, &this->VBO);
	////glGenBuffers(1, &this->EBO);
	////glGenVertexArrays(1, &this->VAO);
	//ErrorChecker::CheckOpenGLError();

	////glBindVertexArray(this->VAO);
	//vao.Bind();
	//// Load data into vertex buffers
	////glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	//vbo.Bind();
	//// A great thing about structs is that their memory layout is sequential for all its items.
	//// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	//// again translates to 3/2 floats which translates to a byte array.
	//glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
	//ErrorChecker::CheckOpenGLError();

	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//ebo.Bind();
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	//ErrorChecker::CheckOpenGLError();

	//// Set the vertex attribute pointers
	//// Vertex Positions
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//ErrorChecker::CheckOpenGLError();
	//// Vertex Normals
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	//ErrorChecker::CheckOpenGLError();

	////glBindVertexArray(0);
	//vao.Unbind();
	//ErrorChecker::CheckOpenGLError();

	vao.Bind();
	{
		vbo.Bind();
		vbo.BindData(vertices.data(), vertices.size() * sizeof(Vertex));

		ebo.Bind();
		ebo.BindData(indices.data(), indices.size() * sizeof(GLuint));

		vao.SetAttribute(0, 3, AttributeType::Float, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		vao.SetAttribute(1, 3, AttributeType::Float, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		vao.SetAttribute(2, 2, AttributeType::Float, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TextureCoords));
	}
	vao.Unbind();
	ErrorChecker::CheckOpenGLError();
}
