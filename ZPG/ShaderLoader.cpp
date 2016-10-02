#include "ShaderLoader.h"
#include <fstream>
#include <iostream>

using namespace std;

ShaderLoader::~ShaderLoader()
{
}

string ShaderLoader::GetContent(const GLchar * path) const
{
	try
	{
		ifstream in(path);
		if (!in.is_open())
			new exception("Could not open file.");
		string content = { istreambuf_iterator<char>(in), istreambuf_iterator<char>() };
		in.close();
		return content;
	}
	catch (const exception& ex)
	{
		cerr << "Exception has been thrown during loading shader from path: " << path << endl;
		cerr << "Reason: " << ex.what() << endl;
	}
	return "";
}

int ShaderLoader::CreateShader(const GLchar *path, const ShaderType type) const
{
	int shader = glCreateShader(type);
	string content = GetContent(path);
	const GLchar* code = content.c_str();
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	CheckShader(shader, type);
	return shader;
}

bool ShaderLoader::CheckShader(const int shader, const ShaderType type) const
{
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cerr << "Compilation of " << ToString(type) << " shader failed: " << infoLog << endl;
	}
	return success == GL_TRUE;
}

string ShaderLoader::ToString(const ShaderType type) const
{
	switch (type)
	{
	case Vertex:
		return "Vertex";
	case Fragment:
		return "Fragment";
	default:
		return "Unknown";
	}
}
