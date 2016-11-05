#include "Triangle.h"

Triangle::Triangle()
{
	GLfloat vertices[] = {
		// Positions			Colors				Normal
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	-1.0f, -1.0f, 0.0f,	// bottom left
		1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, -1.0f, 0.0f,	// bottom right
		0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f,  1.0f, 0.0f,	// top
	};

	vao.Bind();
	{
		vbo.Bind();
		vbo.BindData(vertices, sizeof(vertices));

		// Position
		vao.SetAttribute(0, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(vertices[0]), (GLvoid*)(0 * sizeof(vertices[0])));
		// Color
		vao.SetAttribute(1, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(vertices[0]), (GLvoid*)(3 * sizeof(vertices[0])));
		// Normal
		vao.SetAttribute(2, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(vertices[0]), (GLvoid*)(6 * sizeof(vertices[0])));

		vbo.Unbind();
	}
	vao.Unbind();
}

void Triangle::Render()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
