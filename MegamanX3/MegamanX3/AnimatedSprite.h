#ifndef _ANIMATED_SPRITE_H
#define _ANIMATED_SPRITE_H

#include "Sprite.h"
#include "Timer.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(float framesPerSecond, float animationSpeed = 1.0f, bool isLooping = true);
	virtual ~AnimatedSprite();

	void Initialize(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float startFrame, float endFrame, float maxFramesRow, float frameWidth, float frameHeight);
	void Update();
	void Render(D3DXVECTOR3 position);

	void SetFrameRange(float startFrame, float endFrame);
	void SetFrame(float frame);

	void ResetFrame();
	bool IsFinished();

	void SetReverse(bool reverse);
	bool GetReverse();

	int GetCurrentFrame();

private:
	float currentFrame;
	float previousFrame;
	float maxFrames;
	float startFrame;
	float endFrame;
	float maxFramesRow;

	float animationSpeed;
	float currentSpeed;
	float framesPerSecond;
	bool isLooping;
	bool reverse;
};

#endif