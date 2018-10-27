#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "Texture.h"
#include <vector>

class ResourceManager
{
public:
	~ResourceManager();
	void LoadTextureResource(LPDIRECT3DDEVICE9 device, LPCSTR textureFileName, D3DCOLOR transColor = D3DCOLOR_XRGB(0, 0, 0));
	Texture* GetTextureByName(char *name);

	static ResourceManager* GetInstance();
private:
	ResourceManager();

	std::vector<Texture*> textures;

	static ResourceManager* instance;
};

#endif