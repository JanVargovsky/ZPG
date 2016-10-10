#pragma once
#include "ApplicationController.h"
#include "Scene.h"

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

	inline ApplicationController* GetController() { return controller; }
	inline Scene* GetScene() { return scene; }
private:
	void PrintVersions();
};
