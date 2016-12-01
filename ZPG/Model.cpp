#include "Model.h"
#include "Logger.h"
#include "DependencyResolver.h"
#include "TextureLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/vec3.hpp>
#include <boost/filesystem.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

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

	if (!mesh->HasTangentsAndBitangents())
		Logger::Error("mesh doesnt have a tangents and bitangents");

	for (auto i = 0; i < mesh->mNumVertices; i++)
	{
		auto vertex = mesh->mVertices[i];
		auto normal = mesh->HasNormals() ? mesh->mNormals[i] : aiVector3D();
		auto textureCoords = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : aiVector3D();

		auto tangent = mesh->HasTangentsAndBitangents() ? mesh->mTangents[i] : aiVector3D();
		auto bitangent = mesh->HasTangentsAndBitangents() ? mesh->mBitangents[i] : aiVector3D();

		vertices.push_back(Vertex(
			ParseToVec3(vertex),
			normalize(ParseToVec3(normal)),
			ParseToVec2(textureCoords),
			normalize(ParseToVec3(tangent)),
			normalize(ParseToVec3(bitangent))
		));

		 //Assimp calculates invalid bitangents for some random reason...
		if (mesh->HasTangentsAndBitangents())
		{
			auto &v = vertices.back();
			//Gram–Schmidt process
			v.Tangent = normalize(v.Tangent - dot(v.Tangent, v.Normal) * v.Normal);
			v.Bitangent = cross(v.Tangent, v.Normal);

			const auto e = 0.001;
			float nt = dot(v.Normal, v.Tangent);
			float tb = dot(v.Tangent, v.Bitangent);
			float bn = dot(v.Bitangent, v.Normal);
			if (abs(nt) >= e || abs(tb) >= e || abs(bn) >= e)
				Logger::Error("not ok");
		}
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
		auto textureLoader = DependencyResolver::GetInstance().Resolve<TextureLoader*>();

		auto material = scene->mMaterials[mesh->mMaterialIndex];

		auto diffuseTextures = LoadTextures(textureLoader, material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());

		auto specularTextures = LoadTextures(textureLoader, material, aiTextureType_SPECULAR);
		if (specularTextures.size() == 0)
			specularTextures.push_back(textureLoader->LoadTexture("Models\\Shared", "Specular.png", TextureType_Specular));
		textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());

		auto normalsTextures = LoadTextures(textureLoader, material, aiTextureType_NORMALS);
		if (normalsTextures.size() == 0)
			normalsTextures.push_back(textureLoader->LoadTexture("Models\\Shared", "nor_sand.jpg", TextureType_Normal));
		textures.insert(textures.end(), normalsTextures.begin(), normalsTextures.end());
	}

	return textures;
}

std::vector<Texture*> Model::LoadTextures(TextureLoader *textureLoader, const aiMaterial * material, aiTextureType textureType)
{
	std::vector<Texture*> textures;

	for (auto i = 0; i < material->GetTextureCount(textureType); i++)
	{
		aiString aiName;
		material->GetTexture(textureType, i, &aiName);

		TextureType type = textureType == aiTextureType_DIFFUSE ? TextureType_Diffuse :
			textureType == aiTextureType_SPECULAR ? TextureType_Specular :
			textureType == aiTextureType_NORMALS ? TextureType_Normal :
			TextureType_Unknown;

		auto texture = textureLoader->LoadTexture(directory, aiName.C_Str(), type);
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
