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
public:
	Application();
	~Application();

	void Run();
private:
	GLFWwindow* window;

	// Data
	const float points[3 * 3 + 4 * 4] = {
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
		" frag_colour = vec4(0.f, 0.f, 1.f, 1.f);"
		"}";

	// Methods
	void Initialize();
	void PrintVersions();
	void CheckShaders(const GLuint &shaderProgram);

	// Callbacks
	static void ErrorCallback(int error, const char * description)
	{
		std::cerr << "ERROR: " << description << std::endl;
	}
};
