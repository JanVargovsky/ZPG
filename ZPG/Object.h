#pragma once
#include <glm/vec3.hpp>

#include "Shader.h"
#include "Transform.h"

class Object
{
private:
	const Shader * shader;
	Transform transform;

	GLuint VBO, EBO, VAO;
public:
	Object(Shader * shader);
	~Object();

	void Draw() const;

	//glm::vec3 getPosition() { return position; }
	//void setPosition(glm::vec3 value) { position = value; }
};

