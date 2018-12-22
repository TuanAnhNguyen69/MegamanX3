#include "pch.h"
#include "DownPlatform.h"
#include "Engine.h"

DownPlatform::DownPlatform() : Entity(DownPlatform_ID)
{

}

void DownPlatform::Update()
{
	Entity::Update();
}

void DownPlatform::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"platform", this->width, this->height);
}

int DownPlatform::GetCollidePosition(Entity * entity)
{
	return this->GetPosition().y + this->height / 2 - ((this->GetPosition().x + this->GetWidth() / 2) - entity->GetPosition().x) / 4;
}

DownPlatform::~DownPlatform()
{
}
