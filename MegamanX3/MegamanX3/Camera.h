#ifndef _CAMERA_H
#define _CAMERA_H

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class Camera
{
public:
	Camera(int width, int height);
	~Camera();

	void SetCenter(float x, float y);
	void SetCenter(D3DXVECTOR3 center);

	int GetWidth();
	int GetHeight();

	void Initialize(LPCTSTR filePath);
	void Update(D3DXVECTOR3 center);
	void CheckCameraPath();
	void StopAutoMove();
	void AutoMoveFoward();
	void AutoMoveReverse();
	void Lock();
	void Unlock();
	bool IsLock();
	bool IsAutoMoving();
	int GetAutoMovedDistance();
	void ResetDistance();
	D3DXVECTOR3 GetCenter();
	RECT GetBound();

private:
	std::vector<RECT *> rangeRects;
	RECT * range;
	int width;
	int height;
	bool lock;
	D3DXVECTOR3 center;
	void SetRange(RECT * rect);
	bool autoMoving;
	int autoMovedDistance;
};

#endif