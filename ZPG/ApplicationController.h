#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ApplicationController
{
public:
	void OnError(int error, const char * description);
	void OnKeyChange(GLFWwindow* window, int key, int scancode, int action, int mods);
	void OnMouseMove(GLFWwindow *window, double x, double y);
	void OnMouseButtonChange(GLFWwindow* window, int button, int action, int mode);
	void OnWindowFocus(GLFWwindow* window, int focused);
	void OnWindowIconify(GLFWwindow* window, int iconified);
	void OnWindowSize(GLFWwindow* window, int width, int height);
	void OnMouseScroll(GLFWwindow *window, double xoffset, double yoffset);
};
