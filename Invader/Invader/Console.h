#pragma once

#ifndef __CONSOLE__
#define __CONSOLE__

#define dfSCREEN_WIDTH 81	//�ܼ� ���� 80ĭ + NULL
#define dfSCREEN_HEIGHT 24	//�ܼ� ���� 24ĭ
class CScreenBuffer {
public:
	//----------------------------------
	//�ܼ� ��� ���� �غ� �۾�.
	//----------------------------------
	void cs_Initial(void);
	//----------------------------------
	//�ܼ� ȭ���� Ŀ���� X,Y��ǥ�� �̵���Ų��.
	//----------------------------------

	void cs_MoveCursor(int iPosX, int iPosY);
	//----------------------------------
	//�ܼ� ȭ���� �ʱ�ȭ �Ѵ�.
	//----------------------------------

	void cs_ClearScreen(void);

	void Buffer_Flip(void);

	void Buffer_Clear(void);

	char* GetScreenBufferLine(int lineNum);

	void Sprite_Draw(int iX, int iY, char chSprite);

	//ȭ����۽̱���
	static CScreenBuffer& GetInstance();
private:
	CScreenBuffer() = default;
	char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
};
#endif
