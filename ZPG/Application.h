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
