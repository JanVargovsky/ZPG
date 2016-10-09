#include "Application.h"
#include "Shader.h"

#include <memory>

using namespace std;
using namespace glm;

Application& Application::GetInstance()
{
	static Application instance;
	return instance;
}

Application::Application()
	: Application(new Scene(), new ApplicationController())
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
	glfwSetCursorPosCallback(window, [](GLFWwindow * window, double x, double y) { Application::GetInstance().GetController()->OnMouseMove(window, x, y); });
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

	shared_ptr<Shader> shader = make_shared<Shader>("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
	shader->UseProgram();
	// TODO: Move to camera
	//mat4 viewMatrix = lookAt(vec3(2, 2, 2), vec3(0, 0, 0), vec3(0, 1, 0));
	mat4 viewMatrix = translate(mat4(), glm::vec3(0.0f, 0.0f, -5.0f));
	shader->Send("viewMatrix", viewMatrix);

	// TODO: Use ratio width/height instead of 4/3
	//45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//mat4 projectionMatrix = perspective(radians(45.0f), 4.f / 3.f, 0.0f, 1000.f);
	mat4 projectionMatrix = perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	shader->Send("projectionMatrix", projectionMatrix);
	shader->UnuseProgram();


	vec3 axis[3] = { vec3(0,0,1),vec3(0,1,0), vec3(1,0,0) };
	float x = -1.5f;
	for (size_t i = 0; i < 3; i++)
	{
		auto scaleObject = new Object(shader, [i](Object & o)
		{
			o.GetTransform().scale = abs(sin(glfwGetTime() + i)) / 3 + 0.1f;
		});
		scaleObject->GetTransform().position = vec3(x, 1.3, 0);
		scene->AddObject(scaleObject);

		auto angleObject = new Object(shader, [](Object & o)
		{
			//o.GetTransform().angle = abs(sin(glfwGetTime())) * 90.f;
			o.GetTransform().angle = glfwGetTime() * 50.f;
		});
		angleObject->GetTransform().position = vec3(x, 0, 0);
		angleObject->GetTransform().scale = 0.5f;
		angleObject->GetTransform().axis = axis[i];
		scene->AddObject(angleObject);

		auto positionObject = new Object(shader, [i](Object & o)
		{
			o.GetTransform().position = vec3(sin(glfwGetTime()) + i - 1, -1.3, 0);

			o.GetTransform().scale = abs(sin(glfwGetTime() + i)) / 3 + 0.1f;
			o.GetTransform().angle = (glfwGetTime() + i) * 50.f;

		});
		positionObject->GetTransform().axis = axis[i];
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