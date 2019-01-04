#include "pch.h"
#include "Camera.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Collision.h"

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
			rect->left = posX * 4;
			rect->top = posY * 4;
			rect->right = rect->left + width * 4;
			rect->bottom = rect->top + height * 4;
			rangeRects.push_back(rect);
		}
	}
	if (!rangeRects.empty()) {
		range = rangeRects.at(0);
	}
}

void Camera::Update(D3DXVECTOR3 center)
{
	this->SetCenter(center);

	if (!range) {
		return;
	}

	if (this->GetBound().left <= range->left)
	{
		this->SetCenter(range->left + this->GetWidth() / 2, this->GetCenter().y);
	}

	if (this->GetBound().right >= range->right)
	{
		this->SetCenter(range->right - this->GetWidth() / 2,
			this->GetCenter().y);
	}

	if (this->GetBound().top <= range->top)
	{
		this->SetCenter(this->GetCenter().x, range->top + this->GetHeight() / 2);
	}

	if (this->GetBound().bottom >= range->bottom)
	{
		this->SetCenter(this->GetCenter().x,
			range->bottom - this->GetHeight() / 2);
	}
}

void Camera::CheckCameraPath()
{
	std::vector<RECT*> currentRects;
	int size = rangeRects.size();
	for (int index = 0; index < size; index++)
	{
		if (index == 3) {
			int a = 0;
		}

		if (Collision::IsInside(this->GetBound(), *rangeRects.at(index))) {
			currentRects.push_back(rangeRects.at(index));
		}
	}
	
	size = currentRects.size();
	if (size != 0) {
		range = new RECT();
		range->left = -1;
		range->right = -1;
		range->top = -1;
		range->bottom = -1;

	}
	for (int index = 0; index < size; index++)
	{
		SetRange(currentRects.at(index));
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

void Camera::SetRange(RECT *rect)
{
	if (rect->left < range->left || range->left == -1)
	{
		range->left = rect->left;
	}

	if (rect->right > range->right || range->right == -1)
	{
		range->right = rect->right;
	}

	if (rect->top < range->top || range->top == -1)
	{
		range->top = rect->top;
	}

	if (rect->bottom > range->bottom || range->bottom == -1)
	{
		range->bottom = rect->bottom;
	}
}
