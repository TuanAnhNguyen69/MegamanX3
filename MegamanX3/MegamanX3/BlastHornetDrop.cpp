#include "pch.h"
#include "BlastHornetDrop.h"


BlastHornetDrop::BlastHornetDrop(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
	sprite = new AnimatedSprite(25, 1, true);
	sprite->Initialize(Engine::GetEngine()->GetGraphics()->GetDevice(), "blast_hornet",
		24, 35, 6, 100, 100);
}


BlastHornetDrop::~BlastHornetDrop()
{

}

void BlastHornetDrop::Load()
{
}

void BlastHornetDrop::Update()
{
}

void BlastHornetDrop::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
