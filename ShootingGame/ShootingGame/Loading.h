#pragma once
#define ENEMYCOUNT 5
struct ENEMY {
	//���� ������
	int posX;
	int posY;

	//�� �������� �̵��� �Ÿ�
	int distanceSequence[4];
	//�� �����̵�����
	int moveSequence[4];

	bool liveFlag = true;
};

void Loading();
