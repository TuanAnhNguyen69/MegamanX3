#ifndef _CAMERA_H
#define _CAMERA_H

#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
public:
	Camera(int width, int height);
	~Camera();

	void SetCenter(float x, float y);
	void SetCenter(D3DXVECTOR3 center);

	int GetWidth();
	int GetHeight();

	D3DXVECTOR3 GetCenter();
	RECT GetBound();

private:
	int width;
	int height;
	D3DXVECTOR3 center;
};

#endif