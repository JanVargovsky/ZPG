#include "ApplicationController.h"
#include "Application.h"
#include "Logger.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

using namespace std;
using namespace glm;

void ApplicationController::OnKeyChange(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	keyStates[key] = action != GLFW_RELEASE;
	this->mods = mods;

	if (keyStates[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

	//GLFW_MOD_SHIFT
	//GLFW_MOD_CONTROL
	//GLFW_MOD_ALT

	//printf("Key press [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void ApplicationController::OnMouseMove(GLFWwindow * window, double x, double y)
{
	auto size = Application::GetInstance().GetScene()->GetSize();
	auto xx = size.GetWidth() / 2;
	auto yy = size.GetHeight() / 2;
	GLfloat z;
	glReadPixels(xx, yy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

	auto screenPosition = vec3(xx, yy, z);
	auto view = Application::GetInstance().GetScene()->GetCamera()->GetView();
	auto projection = Application::GetInstance().GetScene()->GetCamera()->GetProjection();
	auto viewPort = Application::GetInstance().GetScene()->GetViewPort();
	auto position = unProject(screenPosition, view, projection, viewPort);

	//Logger::Verbose("object at x=" + to_string(position.x) + ", y=" + to_string(position.y) + ", z=" + to_string(position.z));
}

void ApplicationController::OnMouseButtonChange(GLFWwindow * window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_1)
		{
			GLbyte color[4];
			GLfloat depth;
			GLuint index;

			auto size = Application::GetInstance().GetScene()->GetSize();

			auto x = size.GetWidth() / 2;
			auto y = size.GetHeight() / 2;
			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

			//printf("Clicked on pixel %d, %d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index %u\n",
			//	x, y, color[0], color[1], color[2], color[3], depth, index);

			Logger::Verbose("Clicked on pixel " + to_string(x) + ", " + to_string(y) +
				", color " + to_string((int)color[0]) + " " + to_string((int)color[1]) + " " + to_string((int)color[2]) + " " + to_string((int)color[3]) +
				", depth " + to_string(depth) + ", stencil index " + to_string(index));

			Application::GetInstance().GetScene()->ChangeColor(index);
		}
		else if (button == GLFW_MOUSE_BUTTON_2)
		{
			auto size = Application::GetInstance().GetScene()->GetSize();
			auto x = size.GetWidth() / 2;
			auto y = size.GetHeight() / 2;
			GLfloat z;
			glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

			auto screenPosition = vec3(x, y, z);
			auto view = Application::GetInstance().GetScene()->GetCamera()->GetView();
			auto projection = Application::GetInstance().GetScene()->GetCamera()->GetProjection();
			auto viewPort = Application::GetInstance().GetScene()->GetViewPort();
			auto position = unProject(screenPosition, view, projection, viewPort);


			//position.y = 0;

			Application::GetInstance().GetScene()->SpawnObject(position);
			Logger::Verbose("spawning object at x=" + to_string(position.x) + ", y=" + to_string(position.y) + ", z=" + to_string(position.z));
		}
	}
}

void ApplicationController::OnWindowFocus(GLFWwindow * window, int focused)
{
	//cout << "Window focus " << focused << endl;
}

void ApplicationController::OnWindowIconify(GLFWwindow * window, int iconified)
{
	//cout << "Window iconify " << iconified << endl;
}

void ApplicationController::OnWindowSize(GLFWwindow * window, int width, int height)
{
	//cout << "Window size width: " << width << " height: " << height << endl;
}

void ApplicationController::OnMouseScroll(GLFWwindow * window, double xoffset, double yoffset)
{
	if (IsCameraZoom(yoffset))
		Application::GetInstance().GetScene()->GetCamera()->Move(ParseToCameraZoom(yoffset));
	//cout << "xoffset: " << xoffset << " yoffset: " << yoffset << endl;
}

void ApplicationController::HandleKeys()
{
	const int moveKeys[] = { GLFW_KEY_W , GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D };
	for (auto key : moveKeys)
		if (keyStates[key])
			Application::GetInstance().GetScene()->GetCamera()->Move(ParseToCameraMove(key), mods == GLFW_MOD_SHIFT);

	if (keyStates[GLFW_KEY_SPACE])
	{
		auto direction = mods == GLFW_MOD_SHIFT ? CameraZoom::Out : CameraZoom::In;
		Application::GetInstance().GetScene()->GetCamera()->Move(direction);
	}
}

bool ApplicationController::IsCameraMove(int key)
{
	return key == GLFW_KEY_W ||
		key == GLFW_KEY_S ||
		key == GLFW_KEY_A ||
		key == GLFW_KEY_D;
}

CameraMove ApplicationController::ParseToCameraMove(int key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		return CameraMove::Forward;
	case GLFW_KEY_S:
		return CameraMove::Back;
	case GLFW_KEY_A:
		return CameraMove::Left;
	case GLFW_KEY_D:
		return CameraMove::Right;
	default:
		return CameraMove::Invalid;
	}
}

bool ApplicationController::IsCameraZoom(int key)
{
	return key == -1 || key == 1;
}

CameraZoom ApplicationController::ParseToCameraZoom(int key)
{

	return key == 1 ? CameraZoom::In : CameraZoom::Out;
}
