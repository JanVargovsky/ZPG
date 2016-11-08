#pragma once
#include "Mesh.h"

#include <assimp/scene.h>

#include <vector>

class Model : public IRenderable
{
private:
	std::vector<Mesh*> meshes;
	const std::string path;

public:
	Model(std::string path);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void Initialize();
	void LoadNode(const aiNode* node, const aiScene *scene);
	void LoadMesh(const aiMesh* mesh, const aiScene *scene);
	std::vector<Vertex> LoadVertices(const aiMesh* mesh, const aiScene *scene);
	std::vector<GLuint> LoadIndices(const aiMesh* mesh, const aiScene *scene);
	glm::vec3 ParseToVec3(aiVector3D &v);
};

