#pragma once
#include <GL/glew.h>

#include <iostream>

class ErrorChecker
{
public:
	static void CheckOpenGLError()
	{
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			auto message = glewGetErrorString(err);
			std::cerr << "[E] Open GL error: " << message << std::endl;
		}
	}
};

