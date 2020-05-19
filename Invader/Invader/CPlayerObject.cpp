#include "stdafx.h"
#include "CBaseObject.h"
#include "CPlayerObject.h"
#include "MovementMessage.h"
#include "Console.h"
#include "CObjectManager.h"
CPlayerObject::CPlayerObject(int iX, int iY, ObjectType ot)
	:CBaseObject(iX, iY, ot) {}

bool CPlayerObject::Action(void)
{
	//Movement();
	MovementExecution();
	return true;
}

void CPlayerObject::Draw(void)
{
	CScreenBuffer::GetInstance().Sprite_Draw(iX, iY, 'A');
}

void CPlayerObject::MovementExecution(void)
{
	while (PlayerMessage::GetInstance().isEmpty() != true) {
		int direction;
		PlayerMessage::GetInstance().DeQueue(&direction);
		if (direction == Direction(LEFT)) {
			iX--;
			if (iX < 0) {
				iX = 0;
			}
		}
		if (direction == Direction(RIGHT)) {
			iX++;
			if (iX > dfSCREEN_WIDTH - 2) {
				iX = dfSCREEN_WIDTH - 2;
			}
		}
		if (direction == Direction(UP)) {
			iY--;
			if (iY < 0) {
				iY = 0;
			}
		}
		if (direction == Direction(DOWN)) {
			iY++;
			if (iY > dfSCREEN_HEIGHT - 1) {
				iY = dfSCREEN_HEIGHT - 1;
			}
		}
		if (direction == Direction(ATTACK)) {
			CObjectManager::GetInstance().CreateObject(ObjectType(BULLET), this->iX, this->iY);
		}
	}
}
