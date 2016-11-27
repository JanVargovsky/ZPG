#pragma once
#include "Transform.h"

#include "glm/vec3.hpp"

class Camera;
class IRenderable;
class Program;

class LightRenderHelper
{
#pragma region Singleton
public:
	static LightRenderHelper& GetInstance();

private:
	LightRenderHelper(const LightRenderHelper&) = delete;
	LightRenderHelper& operator=(const LightRenderHelper&) = delete;
	LightRenderHelper();
#pragma endregion

private:
	IRenderable *model;
	Program *program;
	Transform transform;

public:
	void SetCamera(Camera *camera);
	void RenderLight(glm::vec3 position, glm::vec3 color);
};

