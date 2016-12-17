#pragma once
#include "Mesh.h"

#include <assimp/material.h>

#include <string>
#include <unordered_map>

class TextureLoader
{
private:
	std::unordered_map<std::string, Texture*> textures;

public:
	Texture* LoadTexture(std::string directory, std::string fileName, TextureType type);
	Texture* LoadTexture(std::string directory, std::string fileName, std::string name);
	Texture* LoadCubeTexture(std::string directory, std::string names[6]);

private:
	std::string GetFullPath(std::string &directory, std::string &name);
	void SetImage(Texture *texture, std::string path, GLenum type);
};

