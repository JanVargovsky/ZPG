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
	Texture* LoadTexture(std::string directory, std::string name, aiTextureType textureType);

private:
	std::string GetFullPath(std::string &directory, std::string &name);
};

