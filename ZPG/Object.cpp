#include "Object.h"

#include <GLFW/glfw3.h>  

#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

using namespace std;
using namespace glm;

Object::Object(Shader * shader)
	:shader(shader)
{
	GLfloat vertices[] = {

		// 1st Triangle
		//-0.5f, -0.5f, 0.0f, // bottom left
		//0.5f, -0.5f, 0.0f, // bottom right
		//-0.5f,  0.5f, 0.0f, // top left

		//// 2nd Triangle
		//-0.5f, 0.5f, 0.0f, // top left
		//0.5f, 0.5f, 0.0f, // top right
		//0.5f, -0.5f, 0.0f, // bottom right

		//Left triangle
		// Positions			Colors
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f, // bottom left
		1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f, // bottom right
		0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f, // top

		// Right triangle
		-1.0f, -1.0f, 0.0f,		1.0f, 1.0f, 0.0f, // bottom left
		1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 1.0f, // bottom right
		0.0f,  1.0f, 0.0f,		1.0f, 0.0f, 1.0f, // top

		// Two triangles with indices
		//-1.0f, -0.5f, 0.0f, // bottom left
		//0.0f, -0.5f, 0.0f, // bottom middle
		//1.0f, -0.5f, 0.0f, // bottom right
		//-0.5f,  0.5f, 0.0f, // top left
		//0.5f,  0.5f, 0.0f, // top right

		// Square
		//-0.5f, -0.5f, 0.0f, // bottom left
		//-0.5f, 0.5f, 0.0f, // top left
		//0.5f, 0.5f, 0.0f, // top right
		//0.5f, -0.5f, 0.0f, // bottom right
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

	shader->UseProgram();
	//GLuint transformLocation = glGetUniformLocation(shader->GetProgram(), "transform");

	// TODO: Use ratio width/height
	mat4 modelMatrix;
	mat4 viewMatrix = lookAt(vec3(2, 2, 2), vec3(0, 0, 0), vec3(0, 1, 0));

	GLuint viewMatrixLocation = glGetUniformLocation(shader->GetProgram(), "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));

	//45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 projectionMatrix = perspective(radians(45.0f), 4.f / 3.f, 0.0f, 1000.f);
	//mat4 projectionMatrix = glm::mat4(1.0f);
	GLuint projectionMatrixLocation = glGetUniformLocation(shader->GetProgram(), "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));
}

Object::~Object()
{
	if (shader != nullptr)
		delete shader;
	if (VAO != 0)
		glDeleteVertexArrays(1, &VAO);
	if (VBO != 0)
		glDeleteBuffers(1, &VBO);
	if (EBO != 0)
		glDeleteBuffers(1, &EBO);
}

void Object::Draw() const
{
	if (shader == nullptr)
		return;

	shader->UseProgram();
	//GLuint transformLocation = glGetUniformLocation(shader->GetProgram(), "transform");

	glBindVertexArray(VAO);
	// TODO: Use ratio width/height
	// TODO: Replace by Transform
	//mat4 test = transform.Get();
	mat4 modelMatrix;
	mat4 viewMatrix = lookAt(vec3(2, 2, 2), vec3(0, 0, 0), vec3(0, 1, 0));

	GLuint viewMatrixLocation = glGetUniformLocation(shader->GetProgram(), "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));

	//45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 projectionMatrix = perspective(radians(45.0f), 4.f / 3.f, 0.0f, 1000.f);
	//mat4 projectionMatrix = glm::mat4(1.0f);
	GLuint projectionMatrixLocation = glGetUniformLocation(shader->GetProgram(), "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));

	mat4 trans;
	trans = translate(trans, vec3(-0.5f, -0.5f, 0.0f));
	trans = rotate(trans, (GLfloat)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
	trans = scale(trans, vec3(0.25f, 0.25f, 0.25f));

	GLuint modelMatrixLocation = glGetUniformLocation(shader->GetProgram(), "modelMatrix");
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(trans));

	shader->UseProgram();

	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	trans = mat4();
	trans = translate(trans, vec3(-0.5f, 0.5f, 0.0f));
	auto time = (GLfloat)glfwGetTime();
	trans = rotate(trans, -time, vec3(0.0f, 0.0f, 1.0f));
	GLfloat scaleFactor = abs(sin(time)) / 5 + 0.2;
	trans = scale(trans, vec3(scaleFactor));

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(trans));

	glDrawArrays(GL_TRIANGLES, 3, 3);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
