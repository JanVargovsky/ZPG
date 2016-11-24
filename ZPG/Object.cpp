#include "Object.h"

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

Object::Object(Program * program, Model * model)
	: program(program), model(model)
{
	static int id = 10;
	this->id = id++;
}

Object::Object(Program * program, StaticModelBase * model)
	: program(program), staticModel(model)
{
	static int id = 1;
	this->id = id++;
}

void Object::PreRender()
{
	program->Use();
	GetModel()->PreRender();

	program->Send("model", GetTransform().Get());
	if (color.is_initialized())
		program->Send("color", color.get());

	glStencilFunc(GL_ALWAYS, id, 0xFF);
}

void Object::Render()
{
	GetModel()->Render();
}

void Object::PostRender()
{
	GetModel()->PostRender();
	program->Unuse();
}

Transform & Object::GetTransform()
{
	return transform;
}
