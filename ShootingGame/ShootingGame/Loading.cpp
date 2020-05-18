#define _CRT_SECURE_NO_WARNINGS
#include "Loading.h"
#include <stdio.h>
#include <Windows.h>

extern int scene;

ENEMY enemy[ENEMYCOUNT];

void Loading() {
	FILE* fp = fopen("EnemyInfo.txt", "rb");

	//외부파일을 열어 적군 정보 설정
	for (int i = 0; i < sizeof(enemy) / sizeof(ENEMY); i++) {
		fscanf(fp, "position : %d,%d\n", &enemy[i].posY, &enemy[i].posX);
		fscanf(fp, "Distance : %d,%d,%d,%d\n",
			&enemy[i].distanceSequence[0], &enemy[i].distanceSequence[1], &enemy[i].distanceSequence[2], &enemy[i].distanceSequence[3]);
		fscanf(fp, "Sequence : %d,%d,%d,%d\n\n",
			&enemy[i].moveSequence[0], &enemy[i].moveSequence[1], &enemy[i].moveSequence[2], &enemy[i].moveSequence[3]);
	}
	fclose(fp);

	scene = 3;
}