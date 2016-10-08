#pragma once
#include "ApplicationController.h"
#include "Scene.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <iostream>

class Application
{
#pragma region Singleton stuff
public:
	static Application& GetInstance();

private:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application();
	Application(Scene *scene, ApplicationController* controller);
	~Application();
#pragma endregion

private:
	bool initialized;
	ApplicationController *controller;
	Scene *scene;

public:
	bool Initialize();

	void Run();

	ApplicationController* GetController() { return controller; }
	Scene* GetScene() { return scene; }
private:
	void PrintVersions();
};
