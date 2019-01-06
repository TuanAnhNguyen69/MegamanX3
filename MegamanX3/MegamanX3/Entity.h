#ifndef _ENTITY_H
#define _ENTITY_H

#include <d3d9.h>
#include "Sprite.h"

enum EntityId{
	// Player
	Megaman_ID,
	MegamanBullet_ID,

	// Boss
	BlastHornet_ID,
	Byte_ID,
	Shurikein_ID,

	// Creep
	CarryArm_ID,
	HeadGunner_ID,
	Helit_ID,
	NotorBanger_ID,
	Bee_ID,

	// Ground
	Cargo_ID,
	Door_ID,
	Ladder_ID,
	BigElevator_ID,
	SmallElevator_ID,
	HeadBlueConveyor_ID,
	BlueConveyor_ID,
	HeadYellowConveyor_ID,
	YellowConveyor_ID,
	Thorn_ID,
	Box_ID,
	BoxWall_ID,
	Roof_ID,
	BreakPlatform_ID,
	UpGround_ID,
	DownGround_ID,
	Platform_ID,

	//weapon
	Canon_ID,
	GunnerRocket_ID,
	HeliRocket_ID,
	ByteBomb_ID,

	//Item
	SmallEnergy_ID,
	BigEnergy_ID,
	ChimeraArmor_ID
};

class Entity
{
public:
	enum CollisionSide
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
	Entity(EntityId entityId);
	Entity();
	virtual ~Entity();

	void InitializeSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float frameWidth, float frameHeight, float top = 0, float left = 0);
	void InitializeAnimatedSprite(LPDIRECT3DDEVICE9 device, LPCTSTR textureName, float framesPerSecond, float startFrame, float endFrame, float maxFramesRow, float frameWidth, float frameHeight, float animationSpeed = 1.0f, bool isLooping = true);

	virtual void Update();
	virtual void OnCollision(Entity *impactor, Entity::CollisionSide side, Entity::CollisionReturn data);

	virtual void Render();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();
	D3DXVECTOR3 GetVelocity();
	float GetWidth();
	float GetHeight();
	bool GetReverse();
	EntityId GetEntityId();


	void SetSprite(Sprite *sprite);
	void SetTranslation(float x = 0.0f, float y = 0.0f);
	void SetScale(float x = 1.0f, float y = 1.0f);
	void SetPosition(float x = 0.0f, float y = 0.0f);
	void SetBound(int width, int height);
	void SetVelocity(float x = 0.0f, float y = 0.0f);
	void SetReverse(bool reverse);
	void SetPositionX(float x);
	void SetPositionY(float y);

	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void AddVelocityX(float x);
	void AddVelocityY(float y);

	void AddPosition(float x, float y);

	void GoTo(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float speed);
	void GoOn(D3DXVECTOR3 curPoint, D3DXVECTOR3 desPoint, float speed);

	void SetRemove();
	bool IsRemove();
protected:
	int width;
	int height;
private:
	D3DXMATRIX transformMatrix;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 translation;
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	EntityId entityId;
	Sprite *sprite;
	bool reverse;

	bool isRemove;
};

#endif