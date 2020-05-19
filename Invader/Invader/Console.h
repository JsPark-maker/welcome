#pragma once

#ifndef __CONSOLE__
#define __CONSOLE__

#define dfSCREEN_WIDTH 81	//콘솔 가로 80칸 + NULL
#define dfSCREEN_HEIGHT 24	//콘솔 가로 24칸
class CScreenBuffer {
public:
	//----------------------------------
	//콘솔 제어를 위한 준비 작업.
	//----------------------------------
	void cs_Initial(void);
	//----------------------------------
	//콘솔 화면의 커서를 X,Y좌표로 이동시킨다.
	//----------------------------------

	void cs_MoveCursor(int iPosX, int iPosY);
	//----------------------------------
	//콘솔 화면을 초기화 한다.
	//----------------------------------

	void cs_ClearScreen(void);

	void Buffer_Flip(void);

	void Buffer_Clear(void);

	char* GetScreenBufferLine(int lineNum);

	void Sprite_Draw(int iX, int iY, char chSprite);

	//화면버퍼싱글톤
	static CScreenBuffer& GetInstance();
private:
	CScreenBuffer() = default;
	char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
};
#endif
