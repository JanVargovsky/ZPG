#include "Application.h"
#include "Shader.h"
#include <cstdio>

using namespace std;
using namespace glm;

const GLfloat Application::vertices[] = {

	// 1st Triangle
	//-0.5f, -0.5f, 0.0f, // bottom left
	//0.5f, -0.5f, 0.0f, // bottom right
	//-0.5f,  0.5f, 0.0f, // top left

	//// 2nd Triangle
	//-0.5f, 0.5f, 0.0f, // top left
	//0.5f, 0.5f, 0.0f, // top right
	//0.5f, -0.5f, 0.0f, // bottom right

	 //Left triangle
	// Positions			Colors
	-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f, // bottom left
	1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f, // bottom right
	0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f, // top

	// Right triangle
	-1.0f, -1.0f, 0.0f,		1.0f, 1.0f, 0.0f, // bottom left
	1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 1.0f, // bottom right
	0.0f,  1.0f, 0.0f,		1.0f, 0.0f, 1.0f, // top

	// Two triangles with indices
	//-1.0f, -0.5f, 0.0f, // bottom left
	//0.0f, -0.5f, 0.0f, // bottom middle
	//1.0f, -0.5f, 0.0f, // bottom right
	//-0.5f,  0.5f, 0.0f, // top left
	//0.5f,  0.5f, 0.0f, // top right

	// Square
	//-0.5f, -0.5f, 0.0f, // bottom left
	//-0.5f, 0.5f, 0.0f, // top left
	//0.5f, 0.5f, 0.0f, // top right
	//0.5f, -0.5f, 0.0f, // bottom right
};

const GLuint Application::indices[] = {
	0, 1, 3,
	1, 2, 4,
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
	Shader shader("Shaders/shader.vs", "Shaders/shader.frag");

	// Vertex Buffer Objects
	GLuint VBO;
	glGenBuffers(1, &VBO);
	// Element Buffer Objects
	//GLuint EBO;
	//glGenBuffers(1, &EBO);
	// Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Bind the VAO, and then set which VBO it uses and how it is used (attribute pointer)
	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// 0 stands for layout=0
		// Normalized data = data that are not between 0 and 1 will be mapped to those values
		// stride = how big is that
		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);

		// Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	// Unbind VAO
	glBindVertexArray(0);

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		// update other events like input handling
		glfwPollEvents();

		// clear color and depth buffer
		glClearColor(.2f, .3f, .4f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 trans;
		trans = translate(trans, vec3(-0.5f, -0.5f, 0.0f));
		trans = rotate(trans, (GLfloat)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
		trans = scale(trans, vec3(0.25f, 0.25f, 0.25f));

		GLuint transformLocation = glGetUniformLocation(shader.GetProgram(), "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(trans));

		shader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		trans = mat4();
		trans = translate(trans, vec3(-0.5f, 0.5f, 0.0f));
		trans = rotate(trans, (GLfloat)-glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
		GLfloat scaleFactor = abs(sin((GLfloat)glfwGetTime())) / 5 + 0.2;
		trans = scale(trans, vec3(scaleFactor));

		transformLocation = glGetUniformLocation(shader.GetProgram(), "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(trans));

		glDrawArrays(GL_TRIANGLES, 3, 3);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		// put the stuff we�ve been drawing onto the display
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

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

	//GLint nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;
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
