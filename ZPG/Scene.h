#pragma once
#include "Shader.h"
#include "Object.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

class Scene
{
private:
	GLFWwindow* window;
	int width, height;
	bool initialized;

	GLuint VBO, VAO;
	std::vector<std::unique_ptr<Object>> objects;

public:
	Scene(int width = 800, int height = 600);
	~Scene();
	bool Initialize();
	bool CanDraw();
	void Draw();
	void AddObject(Object * object);
	void ChangeViewPort(int width, int height);

	GLFWwindow* GetWindow() { return window; }

private:
	void ChangeViewPort();
};
