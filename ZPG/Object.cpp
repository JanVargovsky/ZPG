#include "Object.h"

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

Object::Object(Program * program, IRenderable *model)
	: program(program), model(model)
{
	static int id = 1;
	this->id = id++;
}

void Object::PreRender()
{
	GetProgram()->Use();
	GetModel()->PreRender();

	GetProgram()->Send("model", GetTransform().Get());
	if (color.is_initialized())
		GetProgram()->Send("color", color.get());

	glStencilFunc(GL_ALWAYS, id, 0xFF);
}

void Object::Render()
{
	GetModel()->Render();
}

void Object::PostRender()
{
	GetModel()->PostRender();
	GetProgram()->Unuse();
}
