#include "Application.h"
#include <cstdio>

using namespace std;

const GLfloat Application::vertices[] = {
	
	// 1st Triangle
	-0.5f, -0.5f, 0.0f, // bottom left
	0.5f, -0.5f, 0.0f, // bottom right
	-0.5f,  0.5f, 0.0f, // top left

	// 2nd Triangle
	-0.5f, 0.5f, 0.0f, // top left
	0.5f, 0.5f, 0.0f, // top right
	0.5f, -0.5f, 0.0f, // bottom right
	
};

const GLuint Application::indices[] = {
	0, 1, 3,
	1, 3, 2,
};

Application::Application()
{
	Initialize();
}

Application::~Application()
{
	glfwDestroyWindow(window);
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
		cerr << "Could not start FLFW3" << endl;
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
	if (window == nullptr)
	{
		cerr << "Failed to create GLFW window" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "Failed to initializate GLEW" << endl;
		exit(EXIT_FAILURE);
	}
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
	//float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::Run()
{
#pragma region School stuff
	/*
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
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	// Create shader program that consist of fragment and vertex shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check shaders
	CheckShaders(shaderProgram);
	*/
#pragma endregion

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	CheckVertexShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertex Buffer Objects
	GLuint VBO;
	glGenBuffers(1, &VBO);
	// Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Bind the VAO, and then set which VBO it uses and how it is used (attribute pointer)
	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 0 stands for layout=0
		// Normalized data = data that are not between 0 and 1 will be mapped to those values
		// stride = how big is that
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(0);

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	// Unbind VAO
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// update other events like input handling
		glfwPollEvents();

		// clear color and depth buffer
		glClearColor(.2f, .3f, .4f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glBindVertexArray(0);

		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
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

void Application::CheckVertexShader(const GLuint & vertexShader)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << endl << infoLog << endl;
	}
}

void Application::CheckShaderProgram(const GLuint & shaderProgram)
{
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		cerr << "Linker failure: " << strInfoLog << endl;
		delete[] strInfoLog;
	}
}
