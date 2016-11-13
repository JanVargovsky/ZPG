#pragma once
#include "Mesh.h"

#include <assimp/scene.h>

#include <vector>
#include <memory>

class Model : public IRenderable
{
private:
	std::vector<std::unique_ptr<Mesh>> meshes;
	const std::string path;
	const std::string directory;

public:
	Model(std::string path);

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void Initialize();
	std::string GetDirectoryFromPath(std::string & path);
	void LoadNode(const aiNode* node, const aiScene *scene);
	void LoadMesh(const aiMesh* mesh, const aiScene *scene);
	std::vector<Vertex> LoadVertices(const aiMesh* mesh, const aiScene *scene);
	std::vector<GLuint> LoadIndices(const aiMesh* mesh, const aiScene *scene);
	std::vector<Texture*> LoadTextures(const aiMesh* mesh, const aiScene *scene);
	std::vector<Texture*> LoadTextures(const aiMaterial* material, aiTextureType textureType);
	inline glm::vec3 ParseToVec3(aiVector3D &v);
	inline glm::vec2 ParseToVec2(aiVector3D &v);
};

