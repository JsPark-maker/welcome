#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "Title.h"
#include "Console.h"

extern int scene;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

void Title() {
	static int time = 0;

	//if (time == 0) {
	//	time = GetTickCount();
		//sprintf(szScreenBuffer, "����Ϸ��� �����̽��� %d�����ÿ�", time);
	//}

	if (time == 0) {
			time = GetTickCount();
	}

	//1�ʵ��� ����
	if (GetTickCount() - time < 1000) {
		strcpy(szScreenBuffer[12], "                                          ����Ϸ��� �����̽��� �����ÿ�.");
	}
	else {
		Buffer_Clear();
		if (GetTickCount() - time >= 2000) {
			time = GetTickCount();
		}
	}

	if (GetAsyncKeyState(VK_SPACE)) {
		scene = 2;
	}
	Buffer_Flip();
}