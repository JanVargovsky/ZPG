#include "Scene.h"
#include "ErrorChecker.h"
#include "ColorUtils.h"

#include <GLFW/glfw3.h>  
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace glm;

Scene::Scene(Camera *camera, int width, int height)
	:camera(camera), size(Size<int>(width, height))
{
	window = nullptr;
}

Scene::~Scene()
{
	if (window != nullptr)
		glfwDestroyWindow(window);

	objects.clear();
	shaders.clear();
	pointLights.clear();
}

bool Scene::Initialize()
{
	window = glfwCreateWindow(size.GetWidth(), size.GetHeight(), "ZPG", nullptr, nullptr);
	if (window == nullptr)
	{
		cerr << "Failed to create GLFW window" << endl;
		return false;
	}
	glfwSetWindowPos(window, 1000, 100);

	camera->OnCameraMove([this](Camera* camera)
	{
		this->SetCamera(camera);
	});
	ChangeViewPort();

	return true;
}

bool Scene::CanRender()
{
	return glfwWindowShouldClose(window) == GL_FALSE;
}

void Scene::Render()
{
	Update();

	for (auto &object : objects)
	{
		object->PreRender();

		auto shader = object->GetShaderProgram();
		shader->Send("pointLightCount", pointLights.size());
		for (int i = 0; i < pointLights.size(); i++)
			pointLights[i]->Send(shader, i);

		object->Render();
		object->PostRender();
	}

	RenderCursor();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}

void Scene::Add(Object * object)
{
	unique_ptr<Object> ptr(object);
	objects.push_back(move(ptr));
}

void Scene::ChangeColor(int id)
{
	Object *obj = nullptr;

	for (auto &o : objects)
		if (o.get()->GetId() == id)
		{
			obj = o.get();
			break;
		}

	if (obj == nullptr)
		return;

	obj->SetColor(ColorUtils::GetRandomColor());
}

void Scene::Add(Program * shader)
{
	unique_ptr<Program> ptr(shader);
	shaders.push_back(move(ptr));
}

void Scene::Add(PointLight * light)
{
	unique_ptr<PointLight> ptr(light);
	pointLights.push_back(move(ptr));
}

void Scene::Add(ModelBase * model)
{
	unique_ptr<ModelBase> ptr(model);
	models.push_back(move(ptr));
}

void Scene::ChangeViewPort()
{
	glViewport(0, 0, size.GetWidth(), size.GetHeight());
}

void Scene::Update()
{
	for (auto &light : pointLights)
		light->Update();

	for (auto &object : objects)
		object->Update();
}

void Scene::RenderCursor()
{
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	const float CURSOR_SIZE = 0.03;
	glBegin(GL_LINES);
		glVertex2f(-CURSOR_SIZE, -CURSOR_SIZE);
		glVertex2f(CURSOR_SIZE, CURSOR_SIZE);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(-CURSOR_SIZE, CURSOR_SIZE);
		glVertex2f(CURSOR_SIZE, -CURSOR_SIZE);
	glEnd();

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void Scene::SetCamera(Camera * camera)
{
	for (auto & program : shaders)
	{
		program->Use();

		program->Send("view", camera->GetView());
		program->Send("projection", camera->GetProjection());

		program->Send("cameraPosition", camera->GetEye());

		program->Unuse();
	}
}

void Scene::ChangeViewPort(int width, int height)
{
	this->size = Size<int>(width, height);
	ChangeViewPort();
}

void Scene::SetCamera()
{
	SetCamera(camera);
}
