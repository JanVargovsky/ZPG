#include "Object.h"

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

Object::Object(Program * program, StaticModelBase * model)
	: program(program), model(model)
{
	static int id = 1;
	this->id = id++;
}

void Object::PreRender()
{
	program->Use();
	model->PreRender();

	program->Send("model", GetTransform().Get());
	if (color.is_initialized())
		program->Send("color", color.get());

	glStencilFunc(GL_ALWAYS, id, 0xFF);
}

void Object::Render()
{
	model->Render();
}

void Object::PostRender()
{
	model->PostRender();
	program->Unuse();
}

Transform & Object::GetTransform()
{
	return transform;
}
