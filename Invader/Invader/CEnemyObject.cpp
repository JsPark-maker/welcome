#include "stdafx.h"
#include "CBaseObject.h"
#include "CEnemyObject.h"
#include "Console.h"
#include "CObjectManager.h"
CEnemyObject::CEnemyObject(int X, int Y, ObjectType ot)
	:CBaseObject(X, Y, ot)
{}

CEnemyObject::~CEnemyObject()
{
}

bool CEnemyObject::Action()
{
	EnemyMovement();
	ShootEnemyBullet();
	return true;
}

void CEnemyObject::Draw()
{
	CScreenBuffer::GetInstance().Sprite_Draw(iX, iY, '@');
}

void CEnemyObject::EnemyMovement()
{
	if (isLeft == true) {
		iX--;
		if (iX < 0) {
			iX = 0;
			isLeft = false;
		}
	}
	else {
		iX++;
		if (iX > dfSCREEN_WIDTH - 2) {
			iX = dfSCREEN_WIDTH - 2;
			isLeft = true;
		}
	}
}

void CEnemyObject::ShootEnemyBullet() {
	if (rand() % 100 <= 3) {
		CObjectManager::GetInstance().CreateObject(ObjectType(ENEMY_BULLET), this->iX, this->iY);
	}
}