#include "Model.h"
#include "Logger.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/vec3.hpp>

#include <vector>

using namespace Assimp;
using namespace std;
using namespace glm;

Model::Model(std::string path)
	:path(path)
{
	Initialize();
}

void Model::PreRender()
{
}

void Model::Render()
{
	for (auto &mesh : meshes)
	{
		mesh->PreRender();
		mesh->Render();
		mesh->PostRender();
	}
}

void Model::PostRender()
{
}

void Model::Initialize()
{
	Importer importer;
	auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || !scene->mRootNode || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE)
	{
		Logger::Error("Failed to load file from path=" + path);
		Logger::Error(importer.GetErrorString());
		return;
	}

	LoadNode(scene->mRootNode, scene);
}

void Model::LoadNode(const aiNode* node, const aiScene *scene)
{
	for (auto i = 0; i < node->mNumMeshes; i++)
	{
		auto meshIndex = node->mMeshes[i];
		auto mesh = scene->mMeshes[meshIndex];
		LoadMesh(mesh, scene);
	}

	for (auto i = 0; i < node->mNumChildren; i++)
		LoadNode(node->mChildren[i], scene);
}

void Model::LoadMesh(const aiMesh * mesh, const aiScene * scene)
{
	auto vertices = LoadVertices(mesh, scene);
	auto indices = LoadIndices(mesh, scene);

	meshes.push_back(new Mesh(vertices, indices));
}

std::vector<Vertex> Model::LoadVertices(const aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> vertices;

	for (auto i = 0; i < mesh->mNumVertices; i++)
	{
		auto vertex = mesh->mVertices[i];
		auto normal = mesh->HasNormals() ? mesh->mNormals[i] : aiVector3D(0);
		vertices.push_back(Vertex(ParseToVec3(vertex), ParseToVec3(normal)));
	}

	return vertices;
}

std::vector<GLuint> Model::LoadIndices(const aiMesh * mesh, const aiScene * scene)
{
	vector<GLuint> indices;

	for (auto i = 0; i < mesh->mNumFaces; i++)
	{
		auto face = mesh->mFaces[i];

		for (auto j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return indices;
}

glm::vec3 Model::ParseToVec3(aiVector3D &v)
{
	return vec3(v.x, v.y, v.z);
}
