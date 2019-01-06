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
}

void Camera::Update(D3DXVECTOR3 center)
{

	if (autoMoving) {
		return;
	}

	CheckCameraPath();

	D3DXVECTOR3 cameraCenter = center;
	
	if (range) {
		if (center.x - this->width / 2 <= range->left)
		{
			cameraCenter.x = range->left + this->GetWidth() / 2;
		}

		if (center.x + this->width / 2 >= range->right)
		{
			cameraCenter.x = range->right - this->GetWidth() / 2;
		}

		if (center.y - this->height / 2 <= range->top)
		{
			cameraCenter.y = range->top + this->GetHeight() / 2;
		}

		if (center.y + this->height / 2 >= range->bottom)
		{
			cameraCenter.y = range->bottom - this->GetHeight() / 2;
		}
	}

	this->SetCenter(cameraCenter);

}

void Camera::CheckCameraPath()
{
	std::vector<RECT*> currentRects;
	RECT * maxCollideRect = NULL;
	float maxCollidePercent = 0;
	int size = rangeRects.size();
	for (int index = 0; index < size; index++)
	{
		if (index == 9 || index == 10 ||index ==11) {
			int a = 0;
		}

		float collidePercent = Collision::GetCollidePercent(this->GetBound(), *rangeRects.at(index));

		if (collidePercent == 100.0) {
			currentRects.push_back(rangeRects.at(index));
		}
		else if (collidePercent > maxCollidePercent){
			maxCollideRect = rangeRects.at(index);
		}
	}

	if (maxCollideRect != nullptr && currentRects.size() == 0) {
		currentRects.push_back(maxCollideRect);
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

void Camera::StopAutoMove()
{
	autoMoving = false;
	autoMovedDistance = 0;
}

void Camera::AutoMove()
{
	autoMoving = true;
	D3DXVECTOR3 center = GetCenter();
	this->SetCenter(center.x + 3, center.y);
	autoMovedDistance += 3;
}

bool Camera::IsAutoMoving()
{
	return autoMoving;
}

int Camera::GetAutoMovedDistance()
{
	return autoMovedDistance;
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
