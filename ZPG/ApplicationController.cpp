#include "ApplicationController.h"

#include <iostream>

using namespace std;

void ApplicationController::OnError(int error, const char * description)
{
	cerr << "ERROR: " << description << endl;
}

void ApplicationController::OnKeyChange(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	//GLFW_MOD_SHIFT
	//GLFW_MOD_CONTROL
	//GLFW_MOD_ALT

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("Key press [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void ApplicationController::OnMouseMove(GLFWwindow * window, double x, double y)
{
	cout << "Cursor change x: " << x << " y: " << y << endl;
}

void ApplicationController::OnMouseButtonChange(GLFWwindow * window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
		cout << "button: " << button << " "
		"action: " << action << " "
		"mode: " << mode << endl;
}

void ApplicationController::OnWindowFocus(GLFWwindow * window, int focused)
{
	cout << "Window focus " << focused << endl;
}

void ApplicationController::OnWindowIconify(GLFWwindow * window, int iconified)
{
	cout << "Window iconify " << iconified << endl;
}

void ApplicationController::OnWindowSize(GLFWwindow * window, int width, int height)
{
	cout << "Window size width: " << width << " height: " << height << endl;
}

void ApplicationController::OnMouseScroll(GLFWwindow * window, double xoffset, double yoffset)
{
	cout << "xoffset: " << xoffset << "yoffset: " << yoffset << endl;
}
