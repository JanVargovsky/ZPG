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
	texture->Bind();
	GetProgram()->Send("skybox", 0);
}

void SkyBox::Render()
{
	GetModel()->Render();
}

void SkyBox::PostRender()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	GetModel()->PostRender();
	texture->Unbind();
	GetProgram()->Unuse();

	glDepthMask(GL_TRUE);
}

void SkyBox::Initialize(std::string names[6])
{
	auto textureLoader = DependencyResolver::GetInstance().Resolve<TextureLoader*>();
	texture = textureLoader->LoadCubeTexture("Models\\SkyBox", names);
}
