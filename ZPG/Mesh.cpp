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

	for (int i = 0; i < textures.size(); i++)
	{
		auto texture = textures[i];
		texture->Bind(i);
	}

	//for (auto texture : textures)
	//	texture->Bind();
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
}

void Mesh::Initialize()
{
	vao.Bind();
	{
		vbo.Bind();
		vbo.BindData(vertices.data(), vertices.size() * sizeof(Vertex));

		ebo.Bind();
		ebo.BindData(indices.data(), indices.size() * sizeof(GLuint));

		vao.SetAttribute(0, 3, AttributeType::Float, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		vao.SetAttribute(1, 3, AttributeType::Float, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		vao.SetAttribute(2, 2, AttributeType::Float, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TextureCoords));
		vao.SetAttribute(3, 3, AttributeType::Float, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));
		vao.SetAttribute(4, 3, AttributeType::Float, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangent));
	}
	vao.Unbind();
	ErrorChecker::CheckOpenGLError();
}
