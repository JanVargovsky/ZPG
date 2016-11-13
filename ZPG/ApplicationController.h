#pragma once
#include "Camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ApplicationController
{
private:
	bool keyStates[512] = {};
	int mods;

public:

	void OnError(int error, const char * description);
	void OnKeyChange(GLFWwindow* window, int key, int scancode, int action, int mods);
	void OnMouseMove(GLFWwindow *window, double x, double y);
	void OnMouseButtonChange(GLFWwindow* window, int button, int action, int mode);
	void OnWindowFocus(GLFWwindow* window, int focused);
	void OnWindowIconify(GLFWwindow* window, int iconified);
	void OnWindowSize(GLFWwindow* window, int width, int height);
	void OnMouseScroll(GLFWwindow *window, double xoffset, double yoffset);

	void HandleKeys();
private:
	bool IsCameraMove(int key);
	CameraMove ParseToCameraMove(int key);
	bool IsCameraZoom(int key);
	CameraZoom ParseToCameraZoom(int key);
};
