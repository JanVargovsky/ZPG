#include "Object.h"

#include <GLFW/glfw3.h>  

#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

using namespace std;
using namespace glm;

Object::Object(std::shared_ptr<Shader> shader)
	:Object(shader, nullptr)
{
}

Object::Object(std::shared_ptr<Shader> shader, function<void(Object &)> update)
	: shader(shader), update(update), VBO(0), EBO(0), VAO(0)
{
	GLfloat vertices[] = {
		// Positions			Colors
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f, // bottom left
		1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f, // bottom right
		0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f, // top
	};

	// TODO: Remove ... Temp

	// Vertex Buffer Objects
	glGenBuffers(1, &VBO);
	// Element Buffer Objects
	//GLuint EBO;
	//glGenBuffers(1, &EBO);
	// Vertex Array Object
	glGenVertexArrays(1, &VAO);

	// Bind the VAO, and then set which VBO it uses and how it is used (attribute pointer)
	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// 0 stands for layout=0
		// Normalized data = data that are not between 0 and 1 will be mapped to those values
		// stride = how big is that
		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);

		// Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	// Unbind VAO
	glBindVertexArray(0);
}

Object::~Object()
{
	if (VAO != 0)
		glDeleteVertexArrays(1, &VAO);
	if (VBO != 0)
		glDeleteBuffers(1, &VBO);
	if (EBO != 0)
		glDeleteBuffers(1, &EBO);
}

void Object::Draw()
{
	if (shader == nullptr)
		return;

	if (update != nullptr)
		update(*this);

	shader->UseProgram();
	glBindVertexArray(VAO);
	mat4 modelMatrix = GetTransform().Get();
	shader->Send("modelMatrix", modelMatrix);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	shader->UnuseProgram();
}

Transform & Object::GetTransform()
{
	return transform;
}
