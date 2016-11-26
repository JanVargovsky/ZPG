#include "Model.h"
#include "Logger.h"
#include "DependencyResolver.h"
#include "TextureLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/vec3.hpp>
#include <boost/filesystem.hpp>

#include <vector>

using namespace Assimp;
using namespace std;
using namespace glm;

Model::Model(std::string path)
	:path(path), directory(GetDirectoryFromPath(path))
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

std::string Model::GetDirectoryFromPath(std::string & path)
{
	boost::filesystem::path p(path);
	return p.parent_path().string();
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
	auto textures = LoadTextures(mesh, scene);

	auto m = new Mesh(vertices, indices, textures);
	meshes.emplace_back(m);
}

std::vector<Vertex> Model::LoadVertices(const aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> vertices;

	for (auto i = 0; i < mesh->mNumVertices; i++)
	{
		auto vertex = mesh->mVertices[i];
		auto normal = mesh->HasNormals() ? mesh->mNormals[i] : aiVector3D();
		auto textureCoords = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : aiVector3D();
		vertices.push_back(Vertex(ParseToVec3(vertex), ParseToVec3(normal), ParseToVec2(textureCoords)));
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

std::vector<Texture*> Model::LoadTextures(const aiMesh * mesh, const aiScene * scene)
{
	std::vector<Texture*> textures;

	if (mesh->mMaterialIndex > 0)
	{
		auto material = scene->mMaterials[mesh->mMaterialIndex];

		auto diffuseTextures = LoadTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());

		auto specularTextures = LoadTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());
	}

	return textures;
}

std::vector<Texture*> Model::LoadTextures(const aiMaterial * material, aiTextureType textureType)
{
	std::vector<Texture*> textures;

	auto textureLoader = DependencyResolver::GetInstance().Resolve<TextureLoader*>();

	for (auto i = 0; i < material->GetTextureCount(textureType); i++)
	{
		aiString aiName;
		material->GetTexture(textureType, i, &aiName);

		auto texture = textureLoader->LoadTexture(directory, aiName.C_Str());
		textures.push_back(texture);
	}

	return textures;
}

glm::vec3 Model::ParseToVec3(aiVector3D &v)
{
	return vec3(v.x, v.y, v.z);
}

glm::vec2 Model::ParseToVec2(aiVector3D & v)
{
	return vec2(v.x, v.y);
}
