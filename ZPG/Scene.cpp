#include "Scene.h"

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
	:camera(camera), width(width), height(height)
{
	window = nullptr;
}

Scene::~Scene()
{
	if (window != nullptr)
		glfwDestroyWindow(window);

	objects.clear();
	shaders.clear();
	lights.clear();
}

bool Scene::Initialize()
{
	window = glfwCreateWindow(width, height, "ZPG", nullptr, nullptr);
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
	for (auto &object : objects)
	{
		object->PreRender();
		for (auto &light : lights)
			light->Send(object->GetShaderProgram());
		object->Render();
		object->PostRender();
	}

	// put the stuff we�ve been drawing onto the display
	glfwSwapBuffers(window);
}

void Scene::Add(Object * object)
{
	unique_ptr<Object> ptr(object);
	objects.push_back(move(ptr));
}

void Scene::Add(Program * shader)
{
	unique_ptr<Program> ptr(shader);
	shaders.push_back(move(ptr));
}

void Scene::Add(LightBase * light)
{
	unique_ptr<LightBase> ptr(light);
	lights.push_back(move(ptr));
}

void Scene::Add(ModelBase * model)
{
	unique_ptr<ModelBase> ptr(model);
	models.push_back(move(ptr));
}

void Scene::ChangeViewPort()
{
	glViewport(0, 0, width, height);
}

void Scene::SetCamera(Camera * camera)
{
	for (auto & shader : shaders)
		camera->Set(shader.get());
}

void Scene::ChangeViewPort(int width, int height)
{
	this->width = width;
	this->height = height;
	ChangeViewPort();
}

void Scene::SetCamera()
{
	SetCamera(camera);
}
