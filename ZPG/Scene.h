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
	Camera* camera;
	int width, height;
	bool initialized;

	GLuint VBO, VAO;
	std::vector<std::unique_ptr<Object>> objects;

public:
	Scene(Camera* camera, int width = 800, int height = 600);
	~Scene();
	bool Initialize();
	bool CanDraw();
	void Draw();
	void AddObject(Object * object);
	void ChangeViewPort(int width, int height);

	inline GLFWwindow* GetWindow() { return window; }
	inline Camera* GetCamera() { return camera; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

private:
	void ChangeViewPort();
};
