#pragma once
#include "CList.h"

class CBaseObject;

class CObjectManager
{
private:
	CObjectManager() = default;
public:
	CList <CBaseObject*> ObjectList;

	static CObjectManager& GetInstance();
	
	~CObjectManager();

	void KeyInput();
	void CreateObject(ObjectType ot, int X, int Y);
	void DestroyObject(CBaseObject* co);
	void Action();
	void CheckEnemyHit();
	void CheckBulletHitTheWall();
	void CheckGameFinishLose();
	void CheckGameFinishWin();
	void Draw();
	void InitChar();
};
