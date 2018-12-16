#include "pch.h"
#include "Platform.h"

Platform::Platform() : Entity(EntityId::Platform_ID)
{
}

Platform::~Platform()
{
}

void Platform::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"platform", this->width, this->height);
}