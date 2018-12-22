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
		std::cout << this->GetPosition().y - this->height / 2 << std::endl;
		return this->GetPosition().y + this->height / 2 - (cbrt(this->GetWidth() / 3) * 20);
	}
	else if (entity->GetPosition().x < this->GetPosition().x - this->GetWidth() / 6) {
		float a = this->GetPosition().y + this->height / 2 - (cbrt(entity->GetPosition().x - (this->GetPosition().x - this->GetWidth() / 2)) * 20);
		std::cout << a << std::endl;
		return this->GetPosition().y + this->height / 2 - (cbrt(entity->GetPosition().x - (this->GetPosition().x - this->GetWidth()/2))* 20);
	}
	else if (entity->GetPosition().x > this->GetPosition().x + this->GetWidth() / 6) {
		float a = this->GetPosition().y + this->height / 2 - (cbrt((this->GetPosition().x + this->GetWidth() / 2) - entity->GetPosition().x) * 20);
		std::cout << a << std::endl;
		return this->GetPosition().y + this->height / 2 - (cbrt((this->GetPosition().x + this->GetWidth() / 2) - entity->GetPosition().x) * 20);
	}
}


Roof::~Roof()
{
}
