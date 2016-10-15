#include "Application.h"
#include "Program.h"
#include "ModelBase.h"
#include "ModelManager.h"
#include "SceneObjectFactory.h"
#include "CameraFactory.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <memory>

using namespace std;
using namespace glm;

Application& Application::GetInstance()
{
	static Application instance;
	return instance;
}

Application::Application()
{
	controller = new ApplicationController;
	CameraFactory cameraFactory;

	currentScene = 0;
	auto camera = cameraFactory.Create(CameraType::Normal);

	scenes.push_back({ SceneType::Trash, shared_ptr<Scene>(new Scene(camera)) });
	//scenes.push_back({ SceneType::FourBalls, shared_ptr<Scene>(new Scene(camera)) });
	initialized = false;
}

Application::~Application()
{
	glfwTerminate();
}

bool Application::Initialize()
{
	if (initialized)
		return true;

	glfwSetErrorCallback([](int error, const char * description) { Application::GetInstance().GetController()->OnError(error, description); });

	if (!glfwInit()) {
		cerr << "Failed to start GLFW" << endl;
		return false;
	}

	for (auto scene : scenes)
	{
		if (!scene.Scene->Initialize())
		{
			cerr << "Failed to initialize scene" << endl;
			return false;
		}
	}

	auto window = GetScene()->GetWindow();

	glfwSetKeyCallback(window, [](GLFWwindow * window, int key, int scancode, int action, int mods) { Application::GetInstance().GetController()->OnKeyChange(window, key, scancode, action, mods); });
	glfwSetCursorPosCallback(window, [](GLFWwindow * window, double x, double y)
	{
		Application::GetInstance().GetController()->OnMouseMove(window, x, y);
		Application::GetInstance().GetScene()->GetCamera()->Rotate(x, y);
	});
	glfwSetMouseButtonCallback(window, [](GLFWwindow * window, int button, int action, int mode) {Application::GetInstance().GetController()->OnMouseButtonChange(window, button, action, mode); });
	glfwSetWindowFocusCallback(window, [](GLFWwindow * window, int focused) {Application::GetInstance().GetController()->OnWindowFocus(window, focused); });
	glfwSetWindowIconifyCallback(window, [](GLFWwindow * window, int iconified) {Application::GetInstance().GetController()->OnWindowIconify(window, iconified); });
	glfwSetWindowSizeCallback(window, [](GLFWwindow * window, int width, int height)
	{
		Application::GetInstance().GetController()->OnWindowSize(window, width, height);
		Application::GetInstance().GetScene()->ChangeViewPort(width, height);
	});
	glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset) {Application::GetInstance().GetController()->OnMouseScroll(window, xoffset, yoffset); });

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initializate GLEW" << endl;
		return false;
	}

	// Disable cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Render by distance
	glEnable(GL_DEPTH_TEST);

	// get version info
	PrintVersions();

	SceneObjectFactory sceneObjectFactory;
	for (auto obj : sceneObjectFactory.GetObjects(SceneType::FourBalls))
		GetScene()->AddObject(obj);

	initialized = true;
	return true;
}

void Application::Run()
{
	if (!initialized)
	{
		cerr << "Trying to run uninitialized application" << endl;
		return;
	}

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (GetScene()->CanRender())
	{
		// update other events like input handling
		glfwPollEvents();

		// clear color and depth buffer
		glClearColor(.2f, .3f, .4f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GetScene()->Render();
	}
}

void Application::PrintVersions()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;
}