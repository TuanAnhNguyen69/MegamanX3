#include "pch.h"
#include "Camera.h"
#include <fstream>
#include <iostream>
#include <sstream>


Camera::Camera(int width, int height)
{
	this->width = width;
	this->height = height;
	center = D3DXVECTOR3(0, 0, 0);
}

Camera::~Camera()
{
}

void Camera::SetCenter(float x, float y)
{
	center = D3DXVECTOR3(x, y, 0);
}

void Camera::SetCenter(D3DXVECTOR3 center)
{
	this->center = center;
}

int Camera::GetWidth()
{
	return width;
}

int Camera::GetHeight()
{
	return height;
}

void Camera::Initialize(LPCTSTR filePath)
{
	std::string objFilePath("Map/");
	objFilePath.append(filePath).append("CAM.txt");
	std::ifstream camera(objFilePath);

	if (camera.is_open())
	{
		float posX, posY; int width, height;
		int count;
		camera >> count;
		std::cout << count;
		for (int i = 0; i < count; i++)
		{
			camera >> posX >> posY >> width >> height;
			RECT * rect = new RECT();
			rect->left = posX;
			rect->top = posY;
			rect->right = posX + width;
			rect->bottom = posY + height;
			rangeRects.push_back(rect);
		}
	}
}

D3DXVECTOR3 Camera::GetCenter()
{
	return center;
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left = (long)(center.x - width / 2);
	bound.right = bound.left + width;
	bound.top = (long)(center.y - height / 2);
	bound.bottom = bound.top + height;

	return bound;
}
