#include "Scene.h"

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <iostream>

using namespace std;
using namespace glm;

Scene::Scene(int width, int height)
	:width(width), height(height)
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

	//glfwGetFramebufferSize(window, &width, &height);
	//float ratio = width / (float)height;

	ChangeViewPort();

	return true;
}

bool Scene::CanDraw()
{
	return glfwWindowShouldClose(window) == GL_FALSE;
}

void Scene::Draw()
{
	for (auto & object : objects)
		object->Draw();

	// put the stuff we’ve been drawing onto the display
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
