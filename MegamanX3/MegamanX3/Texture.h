#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <d3dx9.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool Initialize(LPDIRECT3DDEVICE9 device, LPCSTR textureFileName, D3DCOLOR transColor = D3DCOLOR_XRGB(0, 0, 0));

	LPDIRECT3DTEXTURE9 GetTexture();
	std::string GetName();
	int GetWidth();
	int GetHeight();
private:
	int width;
	int height;
	std::string name;
	LPDIRECT3DTEXTURE9 texture;
};

#endif
