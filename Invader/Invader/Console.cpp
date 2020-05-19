#include "stdafx.h"
#include "Console.h"

HANDLE hConsole;


void CScreenBuffer::cs_Initial(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;
	//--------------------------------------
	//화면의 커서를 안보이게끔 설정한다.
	//--------------------------------------
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1; //커서 크기 1
	//--------------------------------------
	//콘솔화면 핸들을 구한다.
	//--------------------------------------
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}

void CScreenBuffer::cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;

	SetConsoleCursorPosition(hConsole, stCoord);
	//원하는 위치로 커서를 이동시킨다.
}

void CScreenBuffer::cs_ClearScreen(void)
{
	unsigned long dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 100, { 0,0 }, &dw);
}

void CScreenBuffer::Buffer_Flip(void)
{
	int iCnt;
	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(szScreenBuffer[iCnt]); //이차원 배열의 한개의 []은 행을 의미
		//포인터를 출력하는 개념
	}
}

void CScreenBuffer::Buffer_Clear(void)
{
	int iCnt;
	memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0';
	}
}

char* CScreenBuffer::GetScreenBufferLine(int lineNum)
{
	return szScreenBuffer[lineNum];
}

void CScreenBuffer::Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;//화면밖으로 나가는 예외처리
	szScreenBuffer[iY][iX] = chSprite;
}

CScreenBuffer& CScreenBuffer::GetInstance()
{
	static CScreenBuffer screenBuffer;
	return screenBuffer;
}
