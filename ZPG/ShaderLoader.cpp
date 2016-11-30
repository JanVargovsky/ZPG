#include "ShaderLoader.h"
#include <fstream>
#include <iostream>

using namespace std;

unique_ptr<Shader> ShaderLoader::CreateShader(const GLchar *path, const ShaderType type) const
{
	string content = GetContent(path);
	const GLchar* code = content.c_str();

	return unique_ptr<Shader>(new Shader(code, type));
}

string ShaderLoader::GetContent(const GLchar * path) const
{
	try
	{
		ifstream in(path);
		if (!in.is_open())
			new exception("Could not open file.");
		if (!in.good())
			new exception("Some fail occured.");
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

