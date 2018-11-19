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

void AnimatedSprite::Initialize(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float startFrame, float endFrame, float maxFramesRow, float frameWidth, float frameHeight)
{
	Sprite::Initialize(device, textureName);
	currentFrame = 0;
	previousFrame = -1.0f;
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	this->maxFrames = endFrame - startFrame + 1;
	this->maxFramesRow = maxFramesRow;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
}

void AnimatedSprite::Update()
{
	if (maxFrames == 1.0f) {
		return;
	}

	if (currentFrame < maxFrames) {
		float dt = Timer::GetDeltaTime();
		currentSpeed += animationSpeed * dt;
		//std::cout << "Current speed: " << currentSpeed << std::endl;

		if (currentSpeed > framesPerSecond) {
			currentFrame++;
			currentSpeed = 0.0f;

			if (currentFrame >= maxFrames) {
				if (isLooping) {
					currentFrame = 0.0f;
				}
				else {
					currentFrame = maxFrames - 1;
				}
			}
		}
	}

	//std::cout << "Current frame: " << currentFrame << std::endl;

	if (currentFrame == previousFrame) {
		return;
	}

	previousFrame = currentFrame;

	int row = (long)((startFrame + currentFrame) / maxFramesRow);
	int column = (long)(startFrame + currentFrame) % (long)maxFramesRow;

	top = row * frameHeight;
	left = column * frameWidth;
}

void AnimatedSprite::Render(D3DXVECTOR3 position)
{
	Sprite::Render(position);
}

void AnimatedSprite::SetFrameRange(float startFrame, float endFrame)
{
	this->startFrame = startFrame;
	this->endFrame = endFrame;
	this->maxFrames = endFrame - startFrame + 1;
}

void AnimatedSprite::ResetFrame()
{
	currentFrame = 0;
	previousFrame = -1.0f;
}

bool AnimatedSprite::IsFinished()
{
	return currentFrame == maxFrames - 1;
}
