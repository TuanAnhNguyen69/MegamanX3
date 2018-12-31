#include "pch.h"
#include "BlastHornetDie.h"


BlastHornetDie::BlastHornetDie(BlastHornetStateHandler *handler, Entity *entity) : BlastHornetState(handler, entity)
{
}


BlastHornetDie::~BlastHornetDie()
{
}

void BlastHornetDie::Load()
{
}

void BlastHornetDie::Update()
{
}

void BlastHornetDie::OnCollision(Entity * impactor, Entity::CollisionSide side, Entity::CollisionReturn data)
{
}
