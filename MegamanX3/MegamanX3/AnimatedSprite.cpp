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

void AnimatedSprite::Initialize(LPDIRECT3DDEVICE9 device, LPCTSTR textureName)
{
	Sprite::Initialize(device, textureName);
	currentFrame = 0;
	previousFrame = -1.0f;
	maxFrames = 7;
}

void AnimatedSprite::Update()
{
	if (maxFrames == 1.0f) {
		return;
	}

	if (currentFrame < maxFrames) {
		float dt = Timer::GetDeltaTime();
		//std::cout << "Delta time: " << dt << std::endl;
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
					currentFrame = maxFrames;
				}
			}
		}
	}

	//std::cout << "Current frames: " << currentFrame << std::endl;

	if (currentFrame == previousFrame) {
		return;
	}

	previousFrame = currentFrame;
}

void AnimatedSprite::Render(D3DXVECTOR3 position)
{
	rect.top = 400;
	rect.left = (int)(currentFrame * 43) + 93;
	rect.right = rect.left + 43;
	rect.bottom = rect.top + 55;
	Sprite::Render(position, rect);
}
