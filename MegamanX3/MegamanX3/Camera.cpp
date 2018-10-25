#include "pch.h"
#include "Camera.h"


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
