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

bool Texture::Initialize(LPDIRECT3DDEVICE9 device, LPCSTR textureFileName, D3DCOLOR transColor)
{
	std::string tempName(textureFileName);
	name = std::string(tempName.begin(), tempName.end());
	size_t pos = name.find_last_of("/");
	if (pos >= 0) {
		name = name.substr(pos + 1, name.length());
	}
	name = name.substr(0, name.find_last_of("."));
	std::cout << name << std::endl;

	HRESULT result;
	D3DXIMAGE_INFO imageInfo;
	result = D3DXGetImageInfoFromFileA(textureFileName, &imageInfo);

	if (FAILED(result)) {
		MessageBox(nullptr, "D3DXGetImageInfoFromFileA() failed", "Error", MB_OK);
		return false;
	}

	this->width = imageInfo.Width;
	this->height = imageInfo.Height;

	result = D3DXCreateTextureFromFileExA(
		device,
		textureFileName,
		imageInfo.Width,
		imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transColor,
		&imageInfo,
		nullptr,
		&texture
	);

	if (FAILED(result)) {
		MessageBox(nullptr, "D3DXCreateTextureFromFile() failed", "Error", MB_OK);
		return false;
	}

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
