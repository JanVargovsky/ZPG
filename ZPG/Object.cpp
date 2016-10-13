#include "Object.h"

#include <GLFW/glfw3.h>  

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

Object::Object(shared_ptr<Program> program, shared_ptr<ModelBase> model)
	:Object(program, model, nullptr)
{
}

Object::Object(shared_ptr<Program> program, shared_ptr<ModelBase> model, function<void(Object &)> update)
	: program(program), model(model), update(update)
{
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

	model->Use();
	mat4 modelMatrix = GetTransform().Get();
	program->Send("model", modelMatrix);

	program->Send("lightPosition", vec3(3, 3, 3));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	model->Use();
	program->Unuse();
}

Transform & Object::GetTransform()
{
	return transform;
}
