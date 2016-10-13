#include "Triangle.h"


Triangle::Triangle()
{
	GLfloat vertices[] = {
		// Positions			Colors				Normal
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	-1.0f, -1.0f, 0.0f,	// bottom left
		1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, -1.0f, 0.0f,	// bottom right
		0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f,  1.0f, 0.0f,	// top
	};

	vbo.BindData(sizeof(vertices), vertices);
	vao.Bind();
	{
		vbo.Bind();

		// Position
		vao.SetAttribute(0, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		// Color
		vao.SetAttribute(1, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		// Normal
		vao.SetAttribute(2, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

		vbo.Unbind();
	}
	vao.Unbind();
}