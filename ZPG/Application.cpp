#include "Application.h"
#include "Program.h"

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
	: Application(new Scene(new Camera(vec3(0), radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f)), new ApplicationController())
{
}

Application::Application(Scene * scene, ApplicationController * controller)
	: scene(scene), controller(controller)
{
	initialized = false;
}

Application::~Application()
{
	glfwTerminate();
	delete scene;
	delete controller;
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

	if (!scene->Initialize())
	{
		cerr << "Failed to initialize scene" << endl;
		return false;
	}
	auto window = scene->GetWindow();

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

	// get version info
	PrintVersions();

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

	shared_ptr<Program> program = make_shared<Program>("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
	scene->GetCamera()->Set(program.get());

	vec3 axis[3] = { vec3(0,0,1),vec3(0,1,0), vec3(1,0,0) };
	float x = -1.5f;
	for (size_t i = 0; i < 3; i++)
	{
		auto scaleObject = new Object(program, [i](Object & o)
		{
			o.GetTransform().SetScale(abs(sin(glfwGetTime() + i)) / 3 + 0.1f);
		});
		scaleObject->GetTransform().SetPosition(vec3(x, 1.3, 0));
		scene->AddObject(scaleObject);

		auto angleObject = new Object(program, [](Object & o)
		{
			o.GetTransform().SetAngle(glfwGetTime() * 50.f);
		});
		angleObject->GetTransform().SetPosition(vec3(x, 0, 0));
		angleObject->GetTransform().SetScale(0.5f);
		angleObject->GetTransform().SetAxis(axis[i]);
		scene->AddObject(angleObject);

		auto positionObject = new Object(program, [i](Object & o)
		{
			o.GetTransform().SetPosition(vec3(sin(glfwGetTime()) + i - 1, -1.3, 0));
			o.GetTransform().SetScale(abs(sin(glfwGetTime() + i)) / 3 + 0.1f);
			o.GetTransform().SetAngle((glfwGetTime() + i) * 50.f);

		});
		positionObject->GetTransform().SetAxis(axis[i]);
		scene->AddObject(positionObject);

		x += 1.5f;
	}

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (scene->CanDraw())
	{
		// update other events like input handling
		glfwPollEvents();

		// clear color and depth buffer
		glClearColor(.2f, .3f, .4f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene->Draw();
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