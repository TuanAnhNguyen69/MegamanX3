#ifndef _ANIMATED_SPRITE_H
#define _ANIMATED_SPRITE_H

#include "Sprite.h"
#include "Timer.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(float framesPerSecond, float animationSpeed = 1.0f, bool isLooping = true);
	virtual ~AnimatedSprite();

	void Initialize(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float maxFrames, float maxFramesRow, float frameWidth, float frameHeight, float top = 0, float left = 0);
	void Update();
	void Render(D3DXVECTOR3 position);

private:
	float currentFrame;
	float previousFrame;
	float maxFrames;
	float animationSpeed;
	float currentSpeed;
	float framesPerSecond;
	bool isLooping;
	float maxFramesRow;

	float initialTop;
	float initialLeft;
};

#endif