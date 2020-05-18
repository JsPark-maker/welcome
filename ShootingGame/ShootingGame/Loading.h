#pragma once
#define ENEMYCOUNT 5
struct ENEMY {
	//최초 시작점
	int posX;
	int posY;

	//각 방향으로 이동할 거리
	int distanceSequence[4];
	//각 방향이동순서
	int moveSequence[4];

	bool liveFlag = true;
};

void Loading();
