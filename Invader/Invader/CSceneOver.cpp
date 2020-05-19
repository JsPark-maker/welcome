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

	//1�ʵ��� ����
	if (GetTickCount() - time < 1000) {
		strcpy(CScreenBuffer::GetInstance().GetScreenBufferLine(12), "                                          ������ �������ϴ�.");
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