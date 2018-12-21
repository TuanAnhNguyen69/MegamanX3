#include "pch.h"
#include "Roof.h"
#include "Engine.h"

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


Roof::~Roof()
{
}
