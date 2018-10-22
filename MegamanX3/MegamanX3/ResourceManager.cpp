#include "pch.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = NULL;


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	while (!textures.empty()) {
		delete textures[0];
		textures.erase(textures.begin());
	}
}

void ResourceManager::LoadTextureResource(LPDIRECT3DDEVICE9 device, LPCSTR textureFileName)
{
	Texture *texture = new Texture();
	if (!texture->Initialize(device, textureFileName)) {
		delete texture;
		return;
	}
	textures.push_back(texture);
}

Texture * ResourceManager::GetTextureByName(char * name)
{
	for (unsigned int index = 0; index < textures.size(); index++) {
		Texture *texture = textures[index];
		std::string textureName = texture->GetName();

		if (!strcmp(textureName.c_str(), name)) {
			return texture;
		}
	}
	return nullptr;
}

ResourceManager * ResourceManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new ResourceManager();
	}
	return instance;
}
