//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Source.h"

using namespace std;

float points[] = {
	// Triangle points
	0.0f, 0.3f, 0.0f, // bottom left
	0.3f, -0.3f, 0.0f, // bottom right
	-0.3f, -0.3f, 0.0f,  // top left

	// square points
	-0.5f, -0.5f, 0.0f, // bottom left
	-0.5f, 0.5f, 0.0f, // top left
	0.5f, 0.5f, 0.0f, // top right
	0.5f, -0.5f, 0.0f, // bottom right
};

const char* vertex_shader =
"#version 330\n"
"layout(location = 0) in vec3 vp;"
//"out vec4 color;"
"void main() {"
" gl_Position = vec4(vp, 1.0);"
//" color = vec4(vp, 1.0);"
"}";
const char* red_fragment_shader =
"#version 330\n"
//"in vec4 color;"
"out vec4 frag_colour;"
"void main() {"
" frag_colour = vec4(1.f, 0.f, 0.f, 1.f);"
"}";
const char* blue_fragment_shader =
"#version 330\n"
//"in vec4 color;"
"out vec4 frag_colour;"
"void main() {"
" frag_colour = vec4(0.f, 1.f, 0.f, 1.f);"
"}";

static void error_callback(int error, const char* description) { fputs(description, stderr); }

int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
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

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

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
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void CheckShaders(const GLuint &shaderProgram)
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

void PrintVersions()
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
