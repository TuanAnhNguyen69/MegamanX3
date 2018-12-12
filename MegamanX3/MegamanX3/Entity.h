#ifndef _ENTITY_H
#define _ENTITY_H

#include <d3d9.h>
#include "Sprite.h"

enum EntityId{
	// Player
	Megaman,
	MegamanBullet,

	// Boss
	BlastHornet,
	Byte,
	Shurikein,

	// Creep
	CarryArm,
	HeadGunner,
	Helit,
	NotorBanger_ID,
	Bee,

	// Ground
	Cargo,
	Door,
	Ladder,
	BigElevator,
	SmallElevator,
	BlueConveyor,
	YellowConveyor,
	SmallConveyor,
	Thorn,
	Box,
	BoxWall,
	Roof,
	BreakPlatform,
	UpGround,
	DownGround,
	Platform,

	//weapon
	Canon,
	GunnerRocket,
	HeliRocket,
	ByteBomb,

	//Item
	SmallEnergy,
	BigEnergy,
	ChimeraArmor
};

class Entity
{
public:
	enum SideCollisions
	{
		Left, //0
		Right, //1
		Top, //2
		Bottom, //3
		TopLeft, //4
		TopRight, //5
		BottomLeft, //6
		BottomRight, //7
		NotKnow
	};

	struct CollisionReturn
	{
		bool IsCollided;
		RECT RegionCollision;
	};

	friend class EntityManager;
	~Entity();

	void InitializeSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float frameWidth, float frameHeight, float top = 0, float left = 0);
	void InitializeAnimatedSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float framesPerSecond, float startFrame, float endFrame, float maxFramesRow, float frameWidth, float frameHeight, float animationSpeed = 1.0f, bool isLooping = true);

	void Update();
	void Render();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();
	D3DXVECTOR3 GetVelocity();
	float GetWidth();
	float GetHeight();
	bool GetReverse();

	void SetSprite(Sprite *sprite);
	void SetTranslation(float x = 0.0f, float y = 0.0f);
	void SetScale(float x = 1.0f, float y = 1.0f);
	void SetPosition(float x = 0.0f, float y = 0.0f);
	void SetVelocity(float x = 0.0f, float y = 0.0f);
	void SetReverse(bool reverse);

	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void AddVelocityX(float x);
	void AddVelocityY(float y);

	void AddPosition(float x, float y);

	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
private:
	Entity(EntityId entityId);

	D3DXMATRIX transformMatrix;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 translation;
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	EntityId entityId;
	Sprite *sprite;
	bool reverse;
};

#endif