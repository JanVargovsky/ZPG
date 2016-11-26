#include "TextureLoader.h"
#include "Logger.h"

#include <boost/filesystem.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui/highgui.hpp>
#include <boost/algorithm/string/join.hpp>

#include <iostream>

using namespace boost::filesystem;
using namespace boost::algorithm;
using namespace std;
using namespace cv;

Texture* TextureLoader::LoadTexture(std::string directory, std::string name)
{
	string path = GetFullPath(directory, name);
	auto texture = textures[path];
	if (texture == nullptr)
	{
		texture = new Texture(GL_TEXTURE_2D);
		SetImage(texture, path, GL_TEXTURE_2D);
		/*
		cv::Mat image = imread(path, CV_LOAD_IMAGE_COLOR);
		Logger::Verbose("Image " + path + "(" + to_string(image.cols) + " x " + to_string(image.rows) + ") was loaded");
		//imshow(name, image);
		texture->Bind();
		texture->SetImage(image.cols, image.rows, image.ptr(), GL_TEXTURE_2D);
		image.release();
		*/
		textures[path] = texture;
	}
	return texture;
}

Texture * TextureLoader::LoadCubeTexture(std::string directory, std::string names[6])
{
	string key = directory + names[0] + names[1] + names[2] + names[3] + names[4] + names[5];
	auto texture = textures[key];
	if (texture == nullptr)
	{
		texture = new Texture(GL_TEXTURE_CUBE_MAP);

		for (GLuint i = 0; i < 6; i++)
		{
			string path = GetFullPath(directory, names[i]);
			SetImage(texture, path, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			/*cv::Mat image = imread(path, CV_LOAD_IMAGE_COLOR);
			texture->Bind();
			texture->SetImage(image.cols, image.rows, image.ptr(), GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			Logger::Verbose("Image " + names[i] + "(" + to_string(image.cols) + " x " + to_string(image.rows) + ") was loaded");

			image.release();*/
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
	}

	return texture;
}

std::string TextureLoader::GetFullPath(std::string & directory, std::string & name)
{
	path dir(directory);
	path file(name);
	return (dir / file).string();
}

void TextureLoader::SetImage(Texture *texture, std::string path, GLenum type)
{
	cv::Mat image = imread(path, CV_LOAD_IMAGE_COLOR);
	if (!image.rows || !image.cols)
		Logger::Error("Bad image size");
	texture->Bind();
	texture->SetImage(image.cols, image.rows, image.ptr(), type);
	Logger::Verbose("Image " + path + " (" + to_string(image.cols) + " x " + to_string(image.rows) + ") was loaded");

	image.release();
}
