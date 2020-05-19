#include "stdafx.h"
#include "CSceneBase.h"
#include "CSceneOver.h"
#include "Console.h"
void CSceneOver::Action(void)
{
	static int time = 0;

	if (time == 0) {
		CScreenBuffer::GetInstance().Buffer_Clear();
		time = GetTickCount();
	}

	//1초동안 실행
	if (GetTickCount() - time < 1000) {
		strcpy(CScreenBuffer::GetInstance().GetScreenBufferLine(12), "                                          게임이 끝났습니다.");
	}
	else {
		CScreenBuffer::GetInstance().Buffer_Clear();
		if (GetTickCount() - time >= 2000) {
			time = GetTickCount();
			if (GetAsyncKeyState(VK_SPACE)) {
				exit(0);
			}
		}
	}
	CScreenBuffer::GetInstance().Buffer_Flip();
}