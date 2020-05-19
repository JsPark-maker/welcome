#include "stdafx.h"
#include "CSceneBase.h"
#include "CSceneTitle.h"
#include "CSceneManager.h"
#include "Console.h"
void CSceneTitle::Action(void)
{
	static int time = 0;

	if (time == 0) {
		time = GetTickCount();
	}

	//1�ʵ��� ����
	if (GetTickCount() - time < 1000) {
		strcpy(CScreenBuffer::GetInstance().GetScreenBufferLine(12), "                                          ����Ϸ��� �����̽��� �����ÿ�.");
	}
	else {
		CScreenBuffer::GetInstance().Buffer_Clear();
		if (GetTickCount() - time >= 2000) {
			time = GetTickCount();
		}
	}

	if (GetAsyncKeyState(VK_SPACE)) {
		CSceneManager::GetInstance().LoadScene(SceneType(GAME));
	}
	CScreenBuffer::GetInstance().Buffer_Flip();
}
