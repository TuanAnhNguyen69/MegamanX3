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
	Sprite::~Sprite();
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
		int row = (long)(startFrame / maxFramesRow);
		int column = (long)(startFrame) % (long)maxFramesRow;

		top = row * frameHeight;
		left = column * frameWidth;
		return;
	}

	if (reverse) {
		if (currentFrame >= 0) {
			float dt = Timer::GetDeltaTime();
			currentSpeed += animationSpeed * dt;
			//std::cout << "Current speed: " << currentSpeed << std::endl;

			if (currentSpeed > framesPerSecond) {
				currentFrame--;
				currentSpeed = 0.0f;

				if (currentFrame < 0) {
					if (isLooping) {
						currentFrame = maxFrames - 1;
					}
					else {
						currentFrame = 0.0f;
					}
				}
			}
		}

	}
	else {
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

void AnimatedSprite::SetFrame(float frame)
{
	currentFrame = frame;
}

void AnimatedSprite::ResetFrame()
{

	if (!reverse) {
		currentFrame = 0;
		previousFrame = -1.0f;
		return;
	}

	currentFrame = endFrame;
	previousFrame = maxFrames;
}

bool AnimatedSprite::IsFinished()
{
	return currentFrame == maxFrames - 1;
}

void AnimatedSprite::SetReverse(bool reverse)
{
	if (this->reverse != reverse) {
		this->reverse = reverse;
		if (reverse) {
			currentFrame = endFrame;
		}
		else {
			currentFrame = startFrame;
		}
		ResetFrame();
	}
}

bool AnimatedSprite::GetReverse()
{
	return this->reverse;
}

int AnimatedSprite::GetCurrentFrame()
{
	return currentFrame;
}
