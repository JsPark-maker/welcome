#define _CRT_SECURE_NO_WARNINGS
#include "End.h"
#include <stdio.h>
#include <Windows.h>
#include "Console.h"

extern bool winOrLose;
extern char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

void End() {

	Buffer_Clear();

	static int time = 0;

	if (time == 0) {
		time = GetTickCount();
	}

	//1초동안 실행
	if (GetTickCount() - time < 1000) {
		if (winOrLose == true) {
			strcpy(szScreenBuffer[12], "                                                    YOU WIN!!");
		}
		else {
			strcpy(szScreenBuffer[12], "                                                    YOU LOSE!!");
		}
	}
	else {
		Buffer_Clear();
		if (GetTickCount() - time >= 2000) {
			time = GetTickCount();
		}
	}
	Buffer_Flip();
}