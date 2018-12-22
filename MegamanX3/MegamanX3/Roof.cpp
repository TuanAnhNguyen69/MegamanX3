#include "pch.h"
#include "Roof.h"
#include "Engine.h"
#include <math.h>

Roof::Roof() : Entity(Roof_ID)
{

}

void Roof::Update()
{
	Entity::Update();
}

void Roof::Initialize()
{
	this->InitializeSprite(Engine::GetEngine()->GetGraphics()->GetDevice(),
		"platform", this->width, this->height);
}

int Roof::GetCollidePosition(Entity * entity)
{
	if (entity->GetPosition().x < this->GetPosition().x + this->GetWidth() / 6
		&& entity->GetPosition().x > this->GetPosition().x - this->GetWidth() / 6)
	{
		return this->GetPosition().y - this->height / 2;
	}
	else if (entity->GetPosition().x < this->GetPosition().x - this->GetWidth() / 3) {
		return this->GetPosition().y + cbrt(entity->GetPosition().x - (this->GetPosition().x - this->GetWidth()/2));
	}
	else if (entity->GetPosition().x < this->GetPosition().x - this->GetWidth() / 6) {
		return this->GetPosition().y + cbrt(entity->GetPosition().x - (this->GetPosition().x - this->GetWidth() / 2));
	}
	else if (entity->GetPosition().x > this->GetPosition().x + this->GetWidth() / 3) {
		return this->GetPosition().y - cbrt(entity->GetPosition().x - (this->GetPosition().x - this->GetWidth() / 2));
	}
	else if (entity->GetPosition().x > this->GetPosition().x + this->GetWidth() / 2 - this->GetWidth() / 6) {
		return this->GetPosition().y - cbrt(entity->GetPosition().x - (this->GetPosition().x - this->GetWidth() / 2));
	}
}


Roof::~Roof()
{
}
