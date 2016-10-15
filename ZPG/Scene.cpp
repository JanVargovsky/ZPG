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

Scene::Scene(shared_ptr<Camera> camera, int width, int height)
	:camera(camera), width(width), height(height)
{
	window = nullptr;
}

Scene::~Scene()
{
	if (window != nullptr)
		glfwDestroyWindow(window);

	objects.clear();
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

	ChangeViewPort();

	return true;
}

bool Scene::CanRender()
{
	return glfwWindowShouldClose(window) == GL_FALSE;
}

void Scene::Render()
{
	for (auto & object : objects)
	{
		// TODO: Add event to OnCameraMove()
		// TODO: Register event to camera OnCameraMove event in the object, so it calls its Set method
		// TODO: Add 4 balls to scene and lighting in the middle of them

		camera->Set(object->GetShaderProgram().get());

		object->PreRender();
		object->Render();
		object->PostRender();
	}

	// put the stuff we�ve been drawing onto the display
	glfwSwapBuffers(window);
}

void Scene::AddObject(Object * object)
{
	unique_ptr<Object> objectPtr(object);

	objects.push_back(move(objectPtr));
}

void Scene::ChangeViewPort()
{
	glViewport(0, 0, width, height);
}

void Scene::ChangeViewPort(int width, int height)
{
	this->width = width;
	this->height = height;
	ChangeViewPort();
}
