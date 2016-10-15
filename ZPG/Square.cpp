#include "Square.h"

Square::Square()
{
	const float plain[] = {
		1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,

		-1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f

	};

	vbo.BindData(sizeof(plain), plain);
	vao.Bind();
	{
		vbo.Bind();

		// Position
		vao.SetAttribute(0, 3, AttributeType::Float, GL_FALSE, 6 * sizeof(plain[0]), (GLvoid*)0);
		// Normal
		vao.SetAttribute(1, 3, AttributeType::Float, GL_FALSE, 6 * sizeof(plain[0]), (GLvoid*)(3 * sizeof(plain[0])));

		vbo.Unbind();
	}
	vao.Unbind();
}

void Square::Render()
{
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
