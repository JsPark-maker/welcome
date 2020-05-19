#include "stdafx.h"

#include "CList.h"

#include "Console.h"
#include "MovementMessage.h"

#include "CBaseObject.h"
#include "CPlayerObject.h"
#include "CEnemyObject.h"
#include "CBulletObject.h"
#include "CObjectManager.h"

#include "CSceneManager.h"

CObjectManager& CObjectManager::GetInstance()
{
	static CObjectManager ob;
	return ob;
}

///////----???
CObjectManager::~CObjectManager()
{
	for (CList<CBaseObject*>::Iterator itor = ObjectList.Begin();
		itor != ObjectList.end();) {
		delete* itor;
		itor = ObjectList.erase(itor);
	}
}

void CObjectManager::KeyInput()
{
	if (GetAsyncKeyState(VK_LEFT)) {
		PlayerMessage::GetInstance().EnQueue(Direction(LEFT));
	}

	if (GetAsyncKeyState(VK_RIGHT)) {
		PlayerMessage::GetInstance().EnQueue(Direction(RIGHT));
	}

	if (GetAsyncKeyState(VK_UP)) {
		PlayerMessage::GetInstance().EnQueue(Direction(UP));
	}

	if (GetAsyncKeyState(VK_DOWN)) {
		PlayerMessage::GetInstance().EnQueue(Direction(DOWN));
	}

	if (GetAsyncKeyState(VK_SPACE)) {
		PlayerMessage::GetInstance().EnQueue(Direction(ATTACK));
	}
}

void CObjectManager::CreateObject(ObjectType ot, int X, int Y)
{
	if (ot == ObjectType(PLAYER)) {
		ObjectList.Push_back(new CPlayerObject(X, Y, ot));
	}

	if (ot == ObjectType(BULLET)) {
		ObjectList.Push_back(new CBulletObject(X, Y, ot));
	}

	if (ot == ObjectType(ENEMY)) {
		ObjectList.Push_back(new CEnemyObject(X, Y, ot));
	}

	if (ot == ObjectType(ENEMY_BULLET)) {
		ObjectList.Push_back(new CBulletObject(X, Y, ot));
	}
}

//이렇게 되면 이걸 안쓰게 되는데?? 어떻게 되는거지???  고섹추스
void CObjectManager::DestroyObject(CBaseObject* co)
{
	for (CList<CBaseObject*>::Iterator itor = ObjectList.Begin(); itor != ObjectList.end();) {
		if ((*itor) == co) {
			itor = ObjectList.erase(itor);
		}
		else {
			++itor;
		}
	}
	delete co;
}

void CObjectManager::Action()
{
	KeyInput();

	for (CList<CBaseObject*>::Iterator itor = ObjectList.Begin(); itor != ObjectList.end();++itor) {
		(*itor)->Action();
	}

	CheckEnemyHit();

	CheckBulletHitTheWall();

	CheckGameFinishWin();

	CheckGameFinishLose();

}

void CObjectManager::CheckEnemyHit()
{
	for (CList<CBaseObject*>::Iterator itorForEnemy = ObjectList.Begin(); itorForEnemy != ObjectList.end();) {
		bool Flag = true;
		if ((*itorForEnemy)->GetObjectType() == ObjectType(ENEMY)) {
			for (CList<CBaseObject*>::Iterator itorForBullet = ObjectList.Begin(); itorForBullet != ObjectList.end();) {
				if ((*itorForBullet)->GetObjectType() == ObjectType(BULLET) &&
					(*itorForBullet)->GetX() == (*itorForEnemy)->GetX() &&
					(*itorForBullet)->GetY() == (*itorForEnemy)->GetY()) {

					//Collsion을 호출시켜야할것같은데.././..././././
					itorForBullet = ObjectList.erase(itorForBullet);
					itorForEnemy = ObjectList.erase(itorForEnemy);
					Flag = false;
				}
				else {
					++itorForBullet;
				}
			}
		}
		if (Flag)
			++itorForEnemy;
	}
}

void CObjectManager::CheckBulletHitTheWall()
{
	for (CList<CBaseObject*>::Iterator itorForBullet = ObjectList.Begin(); itorForBullet != ObjectList.end();) {
		if ((*itorForBullet)->GetObjectType() == ObjectType(BULLET) &&
			(*itorForBullet)->GetY() == 0) {
			delete* itorForBullet;
			itorForBullet = ObjectList.erase(itorForBullet);
		}
		else if ((*itorForBullet)->GetObjectType() == ObjectType(ENEMY_BULLET) &&
			(*itorForBullet)->GetY() == dfSCREEN_HEIGHT) {
			delete* itorForBullet;
			itorForBullet = ObjectList.erase(itorForBullet);
		}
		else {
			++itorForBullet;
		}
	}
}

void CObjectManager::CheckGameFinishWin()
{
	for (CList<CBaseObject*>::Iterator itor = ObjectList.Begin(); itor != ObjectList.end(); ++itor) {
		if ((*itor)->GetObjectType() == ObjectType(ENEMY))
			break;
		else if (itor == --(ObjectList.end()) && (*itor)->GetObjectType() != ObjectType(ENEMY)) {
			CSceneManager::GetInstance().LoadScene(SceneType(END));
			break;
		}
	}
}

void CObjectManager::CheckGameFinishLose() {
	for (CList<CBaseObject*>::Iterator itorForPlayer = ObjectList.Begin(); itorForPlayer != ObjectList.end(); ++itorForPlayer) {
		if ((*itorForPlayer)->GetObjectType() == ObjectType(PLAYER)) {
			for (CList<CBaseObject*>::Iterator itorForEnemyBullet = ObjectList.Begin(); itorForEnemyBullet != ObjectList.end(); ++itorForEnemyBullet) {
				if ((*itorForEnemyBullet)->GetObjectType() == ObjectType(ENEMY_BULLET)&&
					(*itorForPlayer)->GetX() == (*itorForEnemyBullet)->GetX() &&
					(*itorForPlayer)->GetY() == (*itorForEnemyBullet)->GetY()) {
					CSceneManager::GetInstance().LoadScene(SceneType(END));
					return;
				}
			}
		}
	}
}

void CObjectManager::Draw()
{
	int totalListSize = ObjectList.Size();

	while (totalListSize != 0) {
		ObjectList[totalListSize - 1]->Draw();
		totalListSize--;
	}
}

void CObjectManager::InitChar()
{
	CreateObject(ObjectType(PLAYER), 10, 20);
	FILE* fp = fopen("EnemyInfo.txt", "rb");
	int TotalEnemyCount;
	fscanf(fp, "EnemyCount = %d\n", &TotalEnemyCount);
	for (int EnemyCount = 0; EnemyCount < TotalEnemyCount; EnemyCount++) {
		int EnemyX;
		int EnemyY;
		fscanf(fp, "EnemyX = %d EnemyY = %d\n", &EnemyX, &EnemyY);
		CreateObject(ObjectType(ENEMY), EnemyX, EnemyY);
	}
	fclose(fp);
}
