#include "SkyBox.h"
#include "Logger.h"

#include <boost/filesystem.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui/highgui.hpp>

using namespace std;
using namespace cv;

SkyBox::SkyBox(Program *program, IRenderable *model, std::string names[6])
	:Object(program, model)
{
	Initialize(names);
}

void SkyBox::PreRender()
{
	glDepthMask(GL_FALSE);

	GetProgram()->Use();
	GetModel()->PreRender();
	glActiveTexture(GL_TEXTURE0);
	GetProgram()->Send("skybox", 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
}

void SkyBox::Render()
{
	GetModel()->Render();
}

void SkyBox::PostRender()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	GetModel()->PostRender();
	GetProgram()->Unuse();

	glDepthMask(GL_TRUE);
}

void SkyBox::Initialize(std::string names[6])
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	for (GLuint i = 0; i < 6; i++)
	{
		cv::Mat image = imread("Models/SkyBox/" + names[i], CV_LOAD_IMAGE_COLOR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		Logger::Verbose("Image " + names[i] + "(" + to_string(image.cols) + " x " + to_string(image.rows) + ") was loaded");
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr()
		);

		image.release();
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
