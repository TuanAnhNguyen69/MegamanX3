#include "pch.h"
#include "UpPlatform.h"
#include "Engine.h"

UpPlatform::UpPlatform() : Entity(UpPlatform_ID)
{

}

void UpPlatform::Update()
{
	Entity::Update();
}

void UpPlatform::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"platform", this->width, this->height);
}

int UpPlatform::GetCollidePosition(Entity * entity)
{
	return this->GetPosition().y + this->height / 2 - (entity->GetPosition().x - (this->GetPosition().x - this->GetWidth() / 2)) / 4;

}

UpPlatform::~UpPlatform()
{
}
