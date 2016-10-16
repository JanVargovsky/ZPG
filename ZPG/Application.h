#pragma once
#include "DependencyResolver.h"
#include "ApplicationController.h"
#include "Scene.h"

#include <vector>

class Application
{
#pragma region Singleton stuff
public:
	static Application& GetInstance();

private:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application();
	~Application();
#pragma endregion

private:
	bool initialized;
	ApplicationController *controller;
	Scene *scene;

	//struct NamedScene
	//{
	//	enum SceneType Type;
	//	std::shared_ptr<Scene> Scene;
	//};
	//int currentScene;
	//std::vector<NamedScene> scenes;

public:
	bool Initialize();

	void Run();

	inline ApplicationController* GetController() { return controller; }
	//inline std::shared_ptr<Scene> GetScene() { return scenes[currentScene].Scene; }
	inline Scene* GetScene() { return scene; }
private:
	void PrintVersions();
};
