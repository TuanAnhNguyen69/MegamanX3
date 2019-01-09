#include "pch.h"
#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

Entity::CollisionSide Collision::GetSideCollision(Entity * e1, Entity::CollisionReturn data)
{
	float xCenter = data.RegionCollision.left + (data.RegionCollision.right - data.RegionCollision.left) / 2.0f;
	float yCenter = data.RegionCollision.top + (data.RegionCollision.bottom - data.RegionCollision.top) / 2.0f;

	D3DXVECTOR2 cCenter = D3DXVECTOR2(xCenter, yCenter);
	D3DXVECTOR2 eCenter = { e1->GetPosition().x, e1->GetPosition().y };

	//lay vector noi tam Entity va CollisionRect
	D3DXVECTOR2 vec = cCenter - eCenter;

	//chuan hoa vector
	D3DXVec2Normalize(&vec, &vec);

	/*
	- neu vector chuan hoa co y > 0 =>nam phia ben tren Entity
	- neu vector chuan hoa co y < 0 =>nam phia ben duoi Entity
	- neu vector chuan hoa co x > 0 => nam phia ben phai Entity
	- neu vector chuan hoa co x < 0 => nam phia ben trai Entity
	*/

	if (vec.y < 0)
	{
		//va cham phia ben tren
		//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham top
		if (vec.x <= 0.35f && vec.x >= -0.35f)
		{
			return Entity::Top;
		}
		else if (vec.x > 0.35f && vec.x < 0.8f)
		{
			//goc trong khoang 35 -> 70 phia ben top - right
			return Entity::TopRight;
		}
		else if (vec.x >= 0.8f)
		{
			return Entity::Right;
		}
		else if (vec.x < -0.35f && vec.x >= -0.8f)
		{
			//va cham phia top - left
			return Entity::TopLeft;
		}
		else
		{
			return Entity::Left;
		}
	}
	else
	{
		//va cham phia ben duoi
		//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham top
		if (vec.x <= 0.35f && vec.x >= -0.35)
		{
			return Entity::Bottom;
		}
		else if (vec.x > 0.35 && vec.x < 0.8)
		{
			//goc trong khoang 35 -> 70 phia ben top - right
			return Entity::BottomRight;
		}
		else if (vec.x >= 0.8)
		{
			return Entity::Right;
		}
		else if (vec.x < -0.35f && vec.x > -0.8f)
		{
			//va cham phia top - left
			return Entity::BottomLeft;
		}
		else
		{
			return Entity::Left;
		}
	}

	return Entity::NotKnow;
}

Entity::CollisionReturn Collision::RectAndRect(RECT rect1, RECT rect2)
{
	Entity::CollisionReturn result;

	if (!IsCollide(rect1, rect2))
	{
		result.IsCollided = false;

		return result;
	}

	result.IsCollided = true;

	//chon max Left
	result.RegionCollision.left = rect1.left > rect2.left ? rect1.left : rect2.left;
	//chon max right
	result.RegionCollision.right = rect1.right < rect2.right ? rect1.right : rect2.right;
	//chon min bottom
	result.RegionCollision.bottom = rect1.bottom < rect2.bottom ? rect1.bottom : rect2.bottom;
	//chon max top
	result.RegionCollision.top = rect1.top > rect2.top ? rect1.top : rect2.top;

	return result;
}

Entity::CollisionSide Collision::GetSideCollision(Entity * e1, Entity * e2)
{
	RECT rect1 = e1->GetBound();
	RECT rect2 = e2->GetBound();

	float w = (e1->GetWidth() + e2->GetWidth()) / 2.0f;
	float h = (e1->GetHeight() + e2->GetHeight()) / 2.0f;

	float dx = e1->GetPosition().x - e2->GetPosition().y;
	float dy = e1->GetPosition().x - e2->GetPosition().y;

	if (abs(dx) <= w && abs(dy) <= h)
	{
		/* co va cham*/
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				/*va cham phia tren e1*/
				return Entity::Top;
			}
			else
			{
				/*va cham phia ben phai e1*/
				return Entity::Right;
			}
		}
		else
		{
			if (wy > -hx)
			{
				/*va cham ben trai e1*/
				return Entity::Left;
			}
			else
			{
				/*va cham phia duoi e1*/
				return Entity::Bottom;
			}
		}
	}
	return Entity::NotKnow;
}

bool Collision::RectangleAndCircle(RECT rect, int circlex, int circley, int circleRadius)
{
	int px = circlex;
	int py = circley;

	if (px < rect.left)
		px = rect.left;
	else if (px > rect.right)
		px = rect.right;

	if (py > rect.bottom)
		py = rect.bottom;
	else if (py < rect.top)
		py = rect.top;

	int dx = px - circlex;
	int dy = py - circley;

	return (dx * dx + dy * dy) <= circleRadius * circleRadius;
}

bool Collision::PointAndRectangle(float x, float y, RECT rect)
{
	if (x < rect.left || x > rect.right || y < rect.top || y > rect.bottom)
		return false;

	return true;
}

bool Collision::IsCollide(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}

float Collision::GetCollidePercent(RECT rect1, RECT rect2)
{
	if (rect1.left >= rect2.left && rect1.right <= rect2.right && rect1.top >= rect2.top && rect1.bottom <= rect2.bottom)
	{
		return 100.0;
	}

	if (!IsCollide(rect1, rect2)) {
		return 0.0;
	}

	RECT collisionRegion;

	collisionRegion.left = rect1.left > rect2.left ? rect1.left : rect2.left;
	//chon max right
	collisionRegion.right = rect1.right < rect2.right ? rect1.right : rect2.right;
	//chon min bottom
	collisionRegion.bottom = rect1.bottom < rect2.bottom ? rect1.bottom : rect2.bottom;
	//chon max top
	collisionRegion.top = rect1.top > rect2.top ? rect1.top : rect2.top;

	float rect1Area = GetRectArea(rect1);
	float collisionRegionArea = GetRectArea(collisionRegion);

	return (collisionRegionArea / rect1Area) * 100.0;
}

RECT Collision::GetSweptBroadphaseRect(Entity * entity)
{
	RECT boardPhase;
	boardPhase.left = entity->GetVelocity().x > 0 ? entity->GetBound().left : entity->GetBound().left + entity->GetVelocity().x / 30;
	boardPhase.top = entity->GetVelocity().y > 0 ? entity->GetBound().top : entity->GetBound().top + entity->GetVelocity().y / 30;
	boardPhase.right = entity->GetBound().right + abs(entity->GetVelocity().x / 30);
	boardPhase.bottom = entity->GetBound().bottom + abs(entity->GetVelocity().y / 30);

	return boardPhase;
}

float Collision::SweptAABB(Entity *e1, Entity *e2, Entity::CollisionReturn & data)
{
	float dxEntry, dxExit;
	float dyEntry, dyExit;

	// tìm khoảng cách các cạnh tương ứng
	if (e1->GetVelocity().x > 0.0f)
	{
		dxEntry = e2->GetBound().left - (e1->GetBound().left + e1->GetBound().right - e1->GetBound().left);
		dxExit = (e2->GetBound().left + e2->GetBound().right - e2->GetBound().left) - e1->GetBound().left;
	}
	else
	{
		dxEntry = (e2->GetBound().left + e2->GetBound().right - e2->GetBound().left) - e1->GetBound().left;
		dxExit = e2->GetBound().left - (e1->GetBound().left + e1->GetBound().right - e1->GetBound().left);
	}

	if (e1->GetVelocity().y > 0.0f)
	{
		dyEntry = e2->GetBound().top - (e1->GetBound().top + e1->GetBound().bottom - e1->GetBound().top);
		dyExit = (e2->GetBound().top + e2->GetBound().bottom - e2->GetBound().top) - e1->GetBound().top;
	}
	else
	{
		dyEntry = (e2->GetBound().top + e2->GetBound().bottom - e2->GetBound().top) - e1->GetBound().top;
		dyExit = e2->GetBound().top - (e1->GetBound().top + e1->GetBound().bottom - e1->GetBound().top);
	}

	// tính thời gian từ khoảng cách tính được và vận tốc của đối tượng
	// vận tốc này là trong 1 frame hình nha
	float xEntry, yEntry;
	float xExit, yExit;
	if (e1->GetVelocity().x == 0.0f)
	{
		// đang đứng yên thì bằng vô cực (chia cho  0)
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = dxEntry / e1->GetVelocity().x;
		xExit = dxExit / e1->GetVelocity().x;
	}

	if (e1->GetVelocity().y == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = dyEntry / e1->GetVelocity().y;
		yExit = dyExit / e1->GetVelocity().y;
	}

	// thời gian va chạm là thời gian lớn nhất của 2 trục (2 trục phải cùng tiếp xúc thì mới va chạm)
	float entryTime = xEntry > yEntry ? xEntry : yEntry;
	// thời gian hết va chạm là thời gian của 2 trục, (1 cái ra khỏi là object hết va chạm)
	float exitTime = xExit < yExit ? xExit : yExit;

	if (entryTime < 0 && exitTime > 0) {
		data.IsCollided = true;
		//chon max Left
		data.RegionCollision.left = e1->GetBound().left > e2->GetBound().left ? e1->GetBound().left : e2->GetBound().left;
		//chon max right
		data.RegionCollision.right = e1->GetBound().right < e2->GetBound().right ? e1->GetBound().right : e2->GetBound().right;
		//chon min bottom
		data.RegionCollision.bottom = e1->GetBound().bottom < e2->GetBound().bottom ? e1->GetBound().bottom : e2->GetBound().bottom;
		//chon max top
		data.RegionCollision.top = e1->GetBound().top > e2->GetBound().top ? e1->GetBound().top : e2->GetBound().top;

		return entryTime;
	}

	// kiểm tra xem có thể va chạm không, mình xét ngược lại cho nhanh
	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
	{
		return 1.0f;
		data.IsCollided = false;
	}

	//// lấy hướng va chạm
	//if (xEntry > yEntry)
	//{
	//	if (dxEntry > 0.0f)
	//	{
	//		result =  Entity::CollisionSide::Right;
	//	}
	//	else
	//	{
	//		result =  Entity::CollisionSide::Left;
	//	}
	//}
	//else
	//{
	//	if (dyEntry > 0.0f)
	//	{
	//		result =  Entity::CollisionSide::Top;
	//	}
	//	else
	//	{
	//		result =  Entity::CollisionSide::Bottom;
	//	}
	//}

	// có thì lấy thời gian

	data.IsCollided = true;
	//chon max Left
	data.RegionCollision.left = e1->GetBound().left > e2->GetBound().left ? e1->GetBound().left : e2->GetBound().left;
	//chon max right
	data.RegionCollision.right = e1->GetBound().right < e2->GetBound().right ? e1->GetBound().right : e2->GetBound().right;
	//chon min bottom
	data.RegionCollision.bottom = e1->GetBound().bottom < e2->GetBound().bottom ? e1->GetBound().bottom : e2->GetBound().bottom;
	//chon max top
	data.RegionCollision.top = e1->GetBound().top > e2->GetBound().top ? e1->GetBound().top : e2->GetBound().top;

	return entryTime;
}

float Collision::GetRectArea(RECT rect)
{
	return (rect.right - rect.left) * (rect.bottom - rect.top);
}
