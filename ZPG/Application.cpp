#include "Application.h"
#include <cstdio>

Application::Application()
{
	Initialize();
}

Application::~Application()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::Run()
{
	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//vertex attribute object(VAO)
	GLuint VAO_Triangle = 0;
	glGenVertexArrays(1, &VAO_Triangle); //generate the VAO
	glBindVertexArray(VAO_Triangle); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLuint VAO_Square = 0;
	glGenVertexArrays(1, &VAO_Square); //generate the VAO
	glBindVertexArray(VAO_Square); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Create & compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	// Create & compile fragment shader
	GLuint red_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(red_fragmentShader, 1, &red_fragment_shader, NULL);
	glCompileShader(red_fragmentShader);
	GLuint blue_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(blue_fragmentShader, 1, &blue_fragment_shader, NULL);
	glCompileShader(blue_fragmentShader);
	// Create shader program that consist of fragment and vertex shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, red_fragmentShader);
	glLinkProgram(shaderProgram);

	GLuint shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, blue_fragmentShader);
	glLinkProgram(shaderProgram2);

	// Check shaders
	CheckShaders(shaderProgram);

	while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);

		// draw square
		glBindVertexArray(VAO_Square);
		glDrawArrays(GL_QUADS, 3, 4); //mode,first,count

		glUseProgram(shaderProgram2);
		// draw triangles
		glBindVertexArray(VAO_Triangle);
		glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}
}

void Application::Initialize()
{
	glfwSetErrorCallback(this->ErrorCallback);
	//glfwSetErrorCallback([](int error, const char * description)
	//{
	//	Application::ErrorCallback(error, description);
	//	//this->ErrorCallback(error, description);
	//});
	// glfwSetErrorCallback(Application::ErrorCallback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	// get version info
	PrintVersions();

	// TODO: Create callbacks
	// glfwSetKeyCallback(window, key_callback);
	// glfwSetCursorPosCallback(window, cursor_callback);
	// glfwSetMouseButtonCallback(window, button_callback);
	// glfwSetWindowFocusCallback(window, window_focus_callback);
	// glfwSetWindowIconifyCallback(window, window_iconify_callback);
	// glfwSetWindowSizeCallback(window, window_size_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
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
}

void Application::CheckShaders(const GLuint & shaderProgram)
{
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure : %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}