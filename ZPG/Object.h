#pragma once
#include "IRenderable.h"
#include "Updatable.h"
#include "Program.h"
#include "Transformable.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Model.h"
#include "StaticModelBase.h"

#include <glm/vec3.hpp>
#include <functional>
#include <memory>

class Object : public Updatable, public IRenderable, public Transformable
{
private:
	int id;
	Program *program;
	IRenderable *model;
	boost::optional<glm::vec3> color;
public:
	Object(Program *program, IRenderable *model);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	inline Program* GetProgram() { return program; }
	inline int GetId() { return id; }

	inline IRenderable* GetModel() { return model; }

	inline void SetColor(glm::vec3 c) { color = c;}
};
