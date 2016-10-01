#pragma once
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

#include <iostream>

class Application
{
private:
	GLFWwindow* window;
	static const GLfloat vertices[];
	static const GLuint indices[];

	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;"
		"void main()"
		"{"
		"	gl_Position = vec4(position, 1.0);"
		"}";
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 color;"
		"void main()"
		"{"
		"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
		"}";

	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		//"uniform mat4 ModelMatrix = mat4("
		//"	1.0, 0.0, 0.0, 0.0," // first column 
		//"	0.0, 1.0, 0.0, 0.0," // second column
		//"	0.0, 0.0, 1.0, 0.0," // third column
		//"	0.5, 0.0, 0.0, 1.0);" // last column
		"void main() {"
		" gl_Position = vec4(vp, 1.0);"
		//" gl_Position = ModelMatrix *vec4 (vp, 1);"
		"}";
	const char* fragment_shader =
		"#version 330\n"
		//"in vec4 color;"
		"out vec4 frag_colour;"
		"void main() {"
		" frag_colour = vec4(1.f, 0.f, 0.f, 1.f);"
		"}";

public:
	Application();
	~Application();

	void Run();
private:

	void Initialize();
	void PrintVersions();
	void CheckVertexShader(const GLuint &vertexShader);
	void CheckShaderProgram(const GLuint &shaderProgram);

	// Callbacks
	static void ErrorCallback(int error, const char * description)
	{
		std::cerr << "ERROR: " << description << std::endl;
	}
};
