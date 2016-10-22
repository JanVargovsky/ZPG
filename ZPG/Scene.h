#pragma once
#include "Program.h"
#include "Object.h"
#include "LightBase.h"
#include "Camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

class Scene
{
private:
	GLFWwindow* window;
	Camera* camera;
	int width, height;
	bool initialized;
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Program>> shaders;
	std::vector<std::unique_ptr<LightBase>> lights;
	std::vector<std::unique_ptr<ModelBase>> models;

public:
	Scene(Camera *camera, int width = 800, int height = 600);
	~Scene();
	bool Initialize();
	bool CanRender();
	void Render();
	void Add(Object * object);
	void Add(Program * shader);
	void Add(LightBase * light);
	void Add(ModelBase * model);

	void ChangeViewPort(int width, int height);
	void SetCamera();
	void SetCamera(Camera * camera);

	inline GLFWwindow* GetWindow() { return window; }
	inline Camera* GetCamera() { return camera; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

private:
	void ChangeViewPort();
};
