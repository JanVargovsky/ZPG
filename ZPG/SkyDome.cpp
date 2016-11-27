#include "SkyDome.h"

SkyDome::SkyDome(Program * program, IRenderable * model, std::string textureName, float radius)
	:Object(program, model)
{
	Initialize(textureName);
	GetTransform().SetScale(radius);
}

void SkyDome::PreRender()
{
	//glDepthMask(GL_FALSE);

	GetProgram()->Use();
	GetModel()->PreRender();
	GetProgram()->Send("model", GetTransform().Get());
	texture->Bind();
}

void SkyDome::Render()
{
	GetModel()->Render();
}

void SkyDome::PostRender()
{
	texture->Unbind();
	GetModel()->PostRender();
	GetProgram()->Unuse();

	//glDepthMask(GL_TRUE);
}

void SkyDome::Initialize(std::string textureName)
{
	auto textureLoader = DependencyResolver::GetInstance().Resolve<TextureLoader*>();
	texture = textureLoader->LoadTexture("Models\\SkyDome", textureName);
}
