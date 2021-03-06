#include "Scene.h"
#include "ErrorChecker.h"
#include "ColorUtils.h"
#include "DependencyResolver.h"
#include "ModelManager.h"
#include "StaticModelManager.h"
#include "LightRenderHelper.h"

#include <GLFW/glfw3.h>  
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace glm;

Scene::Scene(Camera *camera, int width, int height)
	:camera(camera), size(Size<int>(width, height))
{
	window = nullptr;
}

Scene::~Scene()
{
	if (window != nullptr)
		glfwDestroyWindow(window);

	objects.clear();
	shaders.clear();
	pointLights.clear();
}

bool Scene::Initialize()
{
	window = glfwCreateWindow(size.GetWidth(), size.GetHeight(), "ZPG", nullptr, nullptr);
	if (window == nullptr)
	{
		cerr << "Failed to create GLFW window" << endl;
		return false;
	}
	glfwSetWindowPos(window, 500, 100);

	camera->OnCameraMove([this](Camera* camera)
	{
		this->SetCamera(camera);
	});
	ChangeViewPort();

	return true;
}

bool Scene::CanRender()
{
	return glfwWindowShouldClose(window) == GL_FALSE;
}

void Scene::Render()
{
	Update();

	for (auto object : objects)
	{
		object->PreRender();

		SetLights(object);

		object->Render();
		object->PostRender();
	}

	// DEBUG Light's position in scene
	LightRenderHelper::GetInstance().SetCamera(camera);
	for (auto l : pointLights)
		LightRenderHelper::GetInstance().RenderLight(l->GetPosition(), ColorUtils::GetColor(255, 215, 21));
	for (auto l : spotLights)
		LightRenderHelper::GetInstance().RenderLight(l->GetPosition(), ColorUtils::GetColor(255, 128, 0));

	RenderCursor();
	// put the stuff we�ve been drawing onto the display
	glfwSwapBuffers(window);
}

Object* Scene::Add(Object *object)
{
	objects.push_back(object);
	return object;
}

void Scene::ChangeColor(int id)
{
	Object *obj = FindObjectById(id);

	if (obj == nullptr)
		return;

	obj->SetColor(ColorUtils::GetRandomColor());
}

void Scene::SpawnObject(glm::vec3 position)
{
	//spotLights[0] = new SpotLight(camera->GetEye(), 1, position - camera->GetEye(), 0.);

	auto modelManager = DependencyResolver::GetInstance().Resolve<ModelManager*>();
	auto staticModelManager = DependencyResolver::GetInstance().Resolve<StaticModelManager*>();

	//IRenderable *model = modelManager->Get(ModelType::ModelType_LowPolyTree);
	IRenderable *model = staticModelManager->Get(StaticModelType::StaticModelType_Sphere);
	auto obj = new Object(Add(new Program("Shaders/Phong")), model);

	obj->GetTransform().SetPosition(position);
	obj->SetColor(ColorUtils::GetRandomColor());

	Add(obj);
}

void Scene::SetTitle(std::string title)
{
	glfwSetWindowTitle(window, title.c_str());
}

Program* Scene::Add(Program *shader)
{
	shaders.push_back(shader);
	return shader;
}

PointLight* Scene::Add(PointLight * light)
{
	pointLights.push_back(light);
	return light;
}

SpotLight * Scene::Add(SpotLight * light)
{
	spotLights.push_back(light);
	return light;
}

DirectionalLight * Scene::Add(DirectionalLight * light)
{
	directionalLight = light;
	return light;
}

void Scene::SetLights(Object * object)
{
	auto shader = object->GetProgram();
	shader->Send("pointLightCount", (int)pointLights.size());
	for (int i = 0; i < (int)pointLights.size(); i++)
		pointLights[i]->Send(shader, i);

	shader->Send("spotLightCount", (int)spotLights.size());
	for (int i = 0; i < (int)spotLights.size(); i++)
		spotLights[i]->Send(shader, i);

	directionalLight->Send(shader);
}

void Scene::ChangeViewPort()
{
	glViewport(0, 0, size.GetWidth(), size.GetHeight());
}

void Scene::Update()
{
	for (auto &light : pointLights)
		light->Update();

	for (auto &light : spotLights)
		light->Update();

	for (auto &object : objects)
		object->Update();
}

void Scene::RenderCursor()
{
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_DEPTH_TEST);

	const float CURSOR_SIZE = 0.03f;
	glColor3f(0, 0, 0);
	glLineWidth(3);
	glBegin(GL_LINES);

	glVertex2f(0, -CURSOR_SIZE);
	glVertex2f(0, CURSOR_SIZE);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-CURSOR_SIZE, 0);
	glVertex2f(CURSOR_SIZE, 0);
	glEnd();

	glEnable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
}

Object* Scene::FindObjectById(int id)
{
	for (auto &o : objects)
		if (o->GetId() == id)
			return o;

	return nullptr;
}

void Scene::SetCamera(Camera * camera)
{
	for (auto & program : shaders)
		SetCamera(program);
}

void Scene::SetCamera(Program * program)
{
	program->Use();

	program->Send("view", camera->GetView());
	program->Send("projection", camera->GetProjection());

	program->Send("cameraPosition", camera->GetEye());

	program->Unuse();
}

void Scene::ChangeViewPort(int width, int height)
{
	this->size = Size<int>(width, height);
	ChangeViewPort();
}

void Scene::SetCamera()
{
	SetCamera(camera);
}
