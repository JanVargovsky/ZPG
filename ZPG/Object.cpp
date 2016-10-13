#include "Object.h"

#include <GLFW/glfw3.h>  

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

Object::Object(std::shared_ptr<Program> program)
	:Object(program, nullptr)
{
}

Object::Object(std::shared_ptr<Program> program, function<void(Object &)> update)
	: program(program), update(update), vbo(new VBO()), vao(new VAO())
{
	GLfloat vertices[] = {
		// Positions			Colors				Normal
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	-1.0f, -1.0f, 0.0f,	// bottom left
		1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, -1.0f, 0.0f,	// bottom right
		0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f,  1.0f, 0.0f,	// top
	};

	vbo->BindData(sizeof(vertices), vertices);
	vao->Bind();
	{
		vbo->Bind();

		// Position
		vao->SetAttribute(0, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		// Color
		vao->SetAttribute(1, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		// Normal
		vao->SetAttribute(2, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

		vbo->Unbind();
	}
	vao->Unbind();
}

Object::~Object()
{
}

void Object::Draw()
{
	if (program == nullptr)
		return;

	if (update != nullptr)
		update(*this);

	program->Use();

	vao->Bind();
	mat4 modelMatrix = GetTransform().Get();
	program->Send("model", modelMatrix);

	program->Send("lightPosition", vec3(3, 3, 3));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	vao->Unbind();
	program->Unuse();
}

Transform & Object::GetTransform()
{
	return transform;
}
