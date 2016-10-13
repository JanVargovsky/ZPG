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

	// Vertex Buffer Objects
	vbo->BindData(sizeof(vertices), vertices);

	//glGenBuffers(1, &VBO);
	// Element Buffer Objects
	//GLuint EBO;
	//glGenBuffers(1, &EBO);
	// Vertex Array Object
	//glGenVertexArrays(1, &VAO);

	// Bind the VAO, and then set which VBO it uses and how it is used (attribute pointer)
	//glBindVertexArray(VAO);
	vao->Bind();
	{
		vbo->Bind();
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
		// 0 stands for layout=0
		// Normalized data = data that are not between 0 and 1 will be mapped to those values
		// stride = how big is that

		// Position
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(0);
		vao->SetAttribute(0, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));

		// Color
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(1);
		vao->SetAttribute(1, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

		// Normal
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(2);
		vao->SetAttribute(2, 3, AttributeType::Float, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));


		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		vbo->Unbind();
	}
	// Unbind VAO
	//glBindVertexArray(0);
	vao->Unbind();
}

Object::~Object()
{
	//if (vao != nullptr)
	//	delete vao;
	//if (vbo != nullptr)
	//	delete vbo;
	//if (ebo != nullptr)
	//	delete ebo;
}

void Object::Draw()
{
	if (program == nullptr)
		return;

	if (update != nullptr)
		update(*this);

	program->Use();
	//glBindVertexArray(VAO);
	vao->Bind();
	mat4 modelMatrix = GetTransform().Get();
	program->Send("model", modelMatrix);

	program->Send("lightPosition", vec3(3, 3, 3));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	//glBindVertexArray(0);
	vao->Unbind();
	program->Unuse();
}

Transform & Object::GetTransform()
{
	return transform;
}
