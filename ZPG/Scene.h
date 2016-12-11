#pragma once
#include "Program.h"
#include "Object.h"
#include "PointLight.h"
#include "Camera.h"
#include "Size.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

class Scene
{
private:
	GLFWwindow* window;
	Camera* camera;
	Size<int> size;
	bool initialized;
	std::vector<Object*> objects;
	std::vector<Program*> shaders;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;
	DirectionalLight *directionalLight;

public:
	Scene(Camera *camera, int width = 800, int height = 600);
	~Scene();
	bool Initialize();
	bool CanRender();
	void Render();
	Object* Add(Object *object);
	Program* Add(Program *shader);
	PointLight* Add(PointLight *light);
	SpotLight* Add(SpotLight *light);
	DirectionalLight* Add(DirectionalLight *light);

	void ChangeViewPort(int width, int height);
	void SetCamera();
	void SetCamera(Camera * camera);
	void SetCamera(Program * program);

	// Actions
	void ChangeColor(int id);
	void SpawnObject(glm::vec3 position);

	void SetTitle(std::string title);

	inline GLFWwindow* GetWindow() { return window; }
	inline Camera* GetCamera() { return camera; }
	inline Size<int> GetSize() { return size; }
	inline glm::vec4 GetViewPort() { return glm::vec4(0, 0, size.GetWidth(), size.GetHeight()); };

private:
	void SetLights(Object * object);
	void ChangeViewPort();
	void Update();
	void RenderCursor();
	Object* FindObjectById(int id);
};
