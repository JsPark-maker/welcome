#include "Console.h"
#include <Windows.h>
#include <stdio.h>

HANDLE hConsole;

char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

void cs_Initial(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;
	//--------------------------------------
	//ȭ���� Ŀ���� �Ⱥ��̰Բ� �����Ѵ�.
	//--------------------------------------
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1; //Ŀ�� ũ�� 1
	//--------------------------------------
	//�ܼ�ȭ�� �ڵ��� ���Ѵ�.
	//--------------------------------------
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}

void cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;

	SetConsoleCursorPosition(hConsole, stCoord);
	//���ϴ� ��ġ�� Ŀ���� �̵���Ų��.
}

void cs_ClearScreen(void)
{
	unsigned long dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 100, { 0,0 }, &dw);
}

void Buffer_Flip(void)
{
	int iCnt;
	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(szScreenBuffer[iCnt]); //������ �迭�� �Ѱ��� []�� ���� �ǹ�
		//�����͸� ����ϴ� ����
	}
}

void Buffer_Clear(void)
{
	int iCnt;
	memset(szScreenBuffer, ' ', dfSCREEN_WIDTH * dfSCREEN_HEIGHT);

	for (iCnt = 0; iCnt < dfSCREEN_HEIGHT; iCnt++)
	{
		szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = '\0';
	}
}

void Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;//ȭ������� ������ ����ó��
	szScreenBuffer[iY][iX] = chSprite;
}
