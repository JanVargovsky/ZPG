#include "TextureLoader.h"
#include "Logger.h"

#include <boost/filesystem.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui/highgui.hpp>

#include <iostream>

using namespace boost::filesystem;
using namespace std;
using namespace cv;

Texture* TextureLoader::LoadTexture(std::string directory, std::string name, aiTextureType textureType)
{
	string path = GetFullPath(directory, name);
	auto texture = textures[path];
	if (texture == nullptr)
	{
		texture = new Texture();
		cv::Mat image = imread(path, CV_LOAD_IMAGE_COLOR);
		Logger::Verbose("Image " + path + "(" + to_string(image.cols) + " x " + to_string(image.rows) + ") was loaded");
		//imshow(name, image);
		texture->SetImage(image.cols, image.rows, image.ptr());
		image.release();

		textures[path] = texture;
	}
	return texture;
}

std::string TextureLoader::GetFullPath(std::string & directory, std::string & name)
{
	path dir(directory);
	path file(name);
	return (dir / file).string();
}
