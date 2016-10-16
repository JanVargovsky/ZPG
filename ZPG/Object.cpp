#include "Object.h"

#include <GLFW/glfw3.h>  

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

Object::Object(Program * program, ModelBase * model)
	: Object(program, model, nullptr)
{
}

Object::Object(Program * program, ModelBase * model, std::function<void(Object&)> update)
	: program(program), model(model), update(update)
{
}

void Object::PreRender()
{
	program->Use();
	model->PreRender();

	program->Send("model", GetTransform().Get());
	program->Send("lightPosition", vec3(0, 3, 0));

	if (update != nullptr)
		update(*this);
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
