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
	bool initialized;

	GLuint VBO, VAO;
	Shader *shader;
	std::vector<std::unique_ptr<Object>> objects;

public:
	Scene();
	~Scene();
	bool Initialize();
	bool CanDraw();
	void Draw();

	void Add(Object * object);

	GLFWwindow* GetWindow() { return window; }
};

