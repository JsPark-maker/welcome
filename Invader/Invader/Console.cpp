#include "stdafx.h"
#include "Console.h"

HANDLE hConsole;


void CScreenBuffer::cs_Initial(void)
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

void CScreenBuffer::cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;

	SetConsoleCursorPosition(hConsole, stCoord);
	//���ϴ� ��ġ�� Ŀ���� �̵���Ų��.
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
		printf(szScreenBuffer[iCnt]); //������ �迭�� �Ѱ��� []�� ���� �ǹ�
		//�����͸� ����ϴ� ����
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
		return;//ȭ������� ������ ����ó��
	szScreenBuffer[iY][iX] = chSprite;
}

CScreenBuffer& CScreenBuffer::GetInstance()
{
	static CScreenBuffer screenBuffer;
	return screenBuffer;
}
