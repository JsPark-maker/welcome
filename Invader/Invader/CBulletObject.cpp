#include "stdafx.h"
#include "CBaseObject.h"
#include "CBulletObject.h"
#include "CObjectManager.h"
#include "Console.h"
CBulletObject::CBulletObject(int X, int Y, ObjectType ot)
	:CBaseObject(X, Y, ot)
{}

CBulletObject::~CBulletObject()
{
}

bool CBulletObject::Action()
{
	if (this->ot == ObjectType(BULLET))
		BulletMovement();
	else if (this->ot == ObjectType(ENEMY_BULLET))
		EnemyBulletMovement();
	return true;
}

void CBulletObject::Draw()
{
	if(this->ot == ObjectType(BULLET))
		CScreenBuffer::GetInstance().Sprite_Draw(iX, iY, '*');
	else if(this->ot == ObjectType(ENEMY_BULLET))
		CScreenBuffer::GetInstance().Sprite_Draw(iX, iY, 'v');

}

void CBulletObject::Collision(CBaseObject* bo)
{
	if (bo->GetObjectType() == ObjectType(ENEMY)) {
		CObjectManager::GetInstance().DestroyObject(this);
		CObjectManager::GetInstance().DestroyObject(bo);
	}
}

void CBulletObject::BulletMovement(void)
{
	iY--;
}

void CBulletObject::EnemyBulletMovement(void)
{
	iY++;
}
