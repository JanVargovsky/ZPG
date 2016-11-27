#include "LightRenderHelper.h"
#include "IRenderable.h"
#include "Program.h"
#include "ModelManager.h"
#include "DependencyResolver.h"
#include "StaticModelManager.h"
#include "Transform.h"
#include "Camera.h"

LightRenderHelper & LightRenderHelper::GetInstance()
{
	static LightRenderHelper instance;
	return instance;
}

LightRenderHelper::LightRenderHelper()
{
	model = DependencyResolver::GetInstance().Resolve<StaticModelManager*>()->Get(StaticModelType::StaticModelType_Cube);
	program = new Program("Shaders\\Light");
	transform = Transform();
	transform.SetScale(0.05f);
}

void LightRenderHelper::RenderLight(glm::vec3 position, glm::vec3 color)
{
	transform.SetPosition(position);
	program->Use();
	program->Send("model", transform.Get());

	program->Send("color", color);
	model->RenderAll();
	program->Unuse();
}

void LightRenderHelper::SetCamera(Camera * camera)
{
	program->Use();
	program->Send("view", camera->GetView());
	program->Send("projection", camera->GetProjection());
	program->Unuse();
}
