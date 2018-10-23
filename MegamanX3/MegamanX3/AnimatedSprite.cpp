#include "pch.h"
#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(float framesPerSecond, float animationSpeed, bool isLooping) : Sprite()
{
	this->framesPerSecond = (1000.0f / framesPerSecond)/1000.0f;
	this->animationSpeed = animationSpeed;
	this->isLooping = isLooping;
	this->currentSpeed = 0;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Initialize(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float maxFrames, float maxFramesRow, float frameWidth, float frameHeight, float top, float left)
{
	Sprite::Initialize(device, textureName);
	currentFrame = 0;
	previousFrame = -1.0f;
	this->maxFrames = maxFrames;
	this->maxFramesRow = maxFramesRow;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->initialTop = top;
	this->initialLeft = left;
}

void AnimatedSprite::Update()
{
	if (maxFrames == 1.0f) {
		return;
	}

	if (currentFrame < maxFrames) {
		float dt = Timer::GetDeltaTime();
		currentSpeed += animationSpeed * dt;
		std::cout << "Current speed: " << currentSpeed << std::endl;

		if (currentSpeed > framesPerSecond) {
			currentFrame++;
			currentSpeed = 0.0f;

			if (currentFrame >= maxFrames) {
				if (isLooping) {
					currentFrame = 0.0f;
				}
				else {
					currentFrame = maxFrames;
				}
			}
		}
	}

	std::cout << "Current frame: " << currentFrame << std::endl;

	if (currentFrame == previousFrame) {
		return;
	}

	previousFrame = currentFrame;

	top = initialTop + ((int)(currentFrame / (maxFramesRow)) * frameHeight);
	left = initialLeft + (((int)currentFrame % (int)maxFramesRow) * frameWidth);

}

void AnimatedSprite::Render(D3DXVECTOR3 position)
{
	Sprite::Render(position);
}
