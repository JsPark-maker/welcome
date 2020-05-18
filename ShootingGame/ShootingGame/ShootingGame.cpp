// ShootingGame.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
#include <Windows.h>
#include <cstdlib>
#include "Console.h"
#include "LinkedList.h"
#include "GameScene.h"
#include "ShootingGame.h"
#include "Title.h"
#include "Loading.h"
#include "End.h"
#pragma comment(lib, "Winmm.lib")

//게임씬
int scene = 0;


bool winOrLose;

int main(void)
{
    timeBeginPeriod(1);
    cs_Initial();
    Buffer_Clear();

    scene = 1;

    srand(GetTickCount());

    while (1) {
        switch (scene) {
        case 1:
            Title();
            break;
        case 2:
            Loading();
            break;
        case 3:
            Play();
            break;
        case 4:
            End();
            break;
        }
        Sleep(40);
    }
}



