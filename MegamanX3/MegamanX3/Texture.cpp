#include "pch.h"
#include "Texture.h"
#include <iostream>

Texture::Texture()
{
	width = 0;
	height = 0;
	texture = nullptr;
}


Texture::~Texture()
{
	if (texture) {
		texture->Release();
		texture = nullptr;
	}
	name.clear();
}

bool Texture::Initialize(LPDIRECT3DDEVICE9 device, LPCSTR textureFileName)
{
	std::string tempName(textureFileName);
	name = std::string(tempName.begin(), tempName.end());
	size_t pos = name.find_last_of("/");
	if (pos >= 0) {
		name = name.substr(pos + 1, name.length());
	}
	name = name.substr(0, name.find_last_of("."));
	std::cout << name;

	HRESULT result = D3DXCreateTextureFromFile(device, textureFileName, &texture);
	if (FAILED(result)) {
		MessageBox(nullptr, "D3DXCreateTextureFromFile() failed", "Error", MB_OK);
		return false;
	}

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	width = desc.Width;
	height = desc.Height;

	return true;
}

LPDIRECT3DTEXTURE9 Texture::GetTexture()
{
	return texture;
}

std::string Texture::GetName() {
	return name;
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}
