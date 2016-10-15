#pragma once
#include "Program.h"
#include "Object.h"
#include "Camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

class Scene
{
private:
	GLFWwindow* window;
	std::shared_ptr<Camera> camera;
	int width, height;
	bool initialized;
	std::vector<std::unique_ptr<Object>> objects;

public:
	Scene(std::shared_ptr<Camera> camera, int width = 800, int height = 600);
	~Scene();
	bool Initialize();
	bool CanDraw();
	void Draw();
	void AddObject(Object * object);
	void ChangeViewPort(int width, int height);

	inline GLFWwindow* GetWindow() { return window; }
	inline Camera* GetCamera() { return camera.get(); }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

private:
	void ChangeViewPort();
};
