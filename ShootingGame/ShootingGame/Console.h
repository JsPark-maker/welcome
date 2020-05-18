#pragma once

#ifndef __CONSOLE__
#define __CONSOLE__

#define dfSCREEN_WIDTH 81	//�ܼ� ���� 80ĭ + NULL
#define dfSCREEN_HEIGHT 24	//�ܼ� ���� 24ĭ

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

void Sprite_Draw(int iX, int iY, char chSprite);
#endif