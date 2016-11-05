#pragma once
#include "Logger.h"

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
			std::string message = (char*)glewGetErrorString(err);
			Logger::Error(message);
		}
	}
};
