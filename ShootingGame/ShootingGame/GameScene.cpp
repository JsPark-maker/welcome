#define _CRT_SECURE_NO_WARNINGS
#include "GameScene.h"
#include "Console.h"
#include <stdio.h>
#include <Windows.h>
#include "MovementMessage.h"
#include "EnemyMovementMessage.h"
#include "LinkedList.h"
#include "Loading.h"

enum MovementType {UP = 1, LEFT, RIGHT, DOWN, ATTACK};

extern int scene;
extern ENEMY enemy[ENEMYCOUNT];
extern bool winOrLose;

PLAYER player;
BULLET bullet[30];

int playerX = 43;
int playerY = 20;

void MessageEnQueue() {
	if (GetAsyncKeyState(VK_UP)) {
		EnQueue(MovementType::UP);
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		EnQueue(MovementType::LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		EnQueue(MovementType::RIGHT);
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		EnQueue(MovementType::DOWN);
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		EnQueue(MovementType::ATTACK);
	}
}

void MessageMovement() {

	int movementType;

	while (1) {
		if (isEmpty() == true) {
			break;
		}
		DeQueue(&movementType);
		if (movementType == MovementType::UP) {
			player.playerY--;
			if (player.playerY == -1) {
				player.playerY++;
			}
		}

		if (movementType == MovementType::LEFT) {
			player.playerX--;
			if (player.playerX == -1) {
				player.playerX++;
			}
		}

		if (movementType == MovementType::RIGHT) {
			player.playerX++;
			if (player.playerX == dfSCREEN_WIDTH - 2) {
				player.playerX--;
			}
		}

		if (movementType == MovementType::DOWN) {
			player.playerY++;
			if (player.playerY == dfSCREEN_HEIGHT - 1) {
				player.playerY--;
			}
		}

		if (movementType == MovementType::ATTACK) {
			//���ݽ���޼ҵ�
			//������������쿡�� ���� ����
			if(player.liveFlag == true)
			ShootBullet(player.playerX, player.playerY);
		}
	}
}

void EnemyMessageEnQueue() {
	//�� ������ �󸶳� �̵��ߴ��� Ȯ��
	static int howManyDistance[ENEMYCOUNT] = { 0 };
	//�� ������ ���° �̵��ܰ迡 �ֳ� Ȯ��
	static int level[ENEMYCOUNT] = { 0 };
	
	//EnQueue�� �� ���� ���ڸ�ŭ �Ǿ���
	for (int enemyNumber = 0; enemyNumber < ENEMYCOUNT; enemyNumber++) {
		//�� ���� �󸶳� ������ Ȯ���ϱ� ���� �Ÿ��� ������
		//���� �� ������ �Ÿ��� ��� �Ҹ��ϰ� �ٸ� �������� Ʋ���
		//�ٽ� �ش� ��ȣ�� ���� �̵��Ÿ��� 0���� �ʱ�ȭ�� ����������Ѵ�
		howManyDistance[enemyNumber]++;
		//���⼭ ������ �ʿ���
		//�ܿ��Ÿ��� �������� ���
		if (howManyDistance[enemyNumber] <= enemy[enemyNumber].distanceSequence[level[enemyNumber]]) {
			EnemyEnQueue(enemy[enemyNumber].moveSequence[level[enemyNumber]]);
		}
		//�ش� ���������� �ܿ��Ÿ��� ���� ���
		else if (howManyDistance[enemyNumber] > enemy[enemyNumber].distanceSequence[level[enemyNumber]]) {
			//level[i]�� ���� 3�� ��� �� ��ƾ�� ���Ҵ�.
			if (level[enemyNumber] == 3) {
				level[enemyNumber] = 0;
				EnemyEnQueue(enemy[enemyNumber].moveSequence[0]);
			}
			else {
				level[enemyNumber]++;
				EnemyEnQueue(enemy[enemyNumber].moveSequence[level[enemyNumber]]);
			}
			//EnQueue�� �ѹ������Ƿ� �Ÿ��� �̵��Ѱ��̱⶧���� 1�� �־���
			howManyDistance[enemyNumber] = 1;
		}
	}
}

void EnemyMessageMovement() {

	int enemyNumber = 0;
	int movementType = 0;

	for (;;) {
		if (EnemyisEmpty()) {
			break;
		}
		EnemyDeQueue(&movementType);
		if (movementType == MovementType::UP) {
			enemy[enemyNumber].posY--;
		}
		if (movementType == MovementType::LEFT) {
			enemy[enemyNumber].posX--;
		}
		if (movementType == MovementType::RIGHT) {
			enemy[enemyNumber].posX++;
		}
		if (movementType == MovementType::DOWN) {
			enemy[enemyNumber].posY++;
		}
		enemyNumber++;
	}
}

void EnemyAttack() {
	for (int enemyNumber = 0; enemyNumber < ENEMYCOUNT; enemyNumber++) {
		
		//1�ۼ�Ʈ Ȯ���� �Ѿ��� �߻�
		if (enemy[enemyNumber].liveFlag == true && rand() % 100 <= 1) {
			EnemyShootBullet(enemy[enemyNumber].posX, enemy[enemyNumber].posY);
		}
	}
}

void EnemyShootBullet(int enemyPosX, int enemyPosY) {
	//�� �ؿ��� �Ѿ��� ����
	NodeAdd(enemyPosX, enemyPosY + 1);
}



void MoveEnemyBullet() {
	for (int listIndex = 0; listIndex < GetLinkedListSize(); listIndex++) {
		LinkedListIndex(listIndex)->bulletY++;

		if (LinkedListIndex(listIndex)->bulletY == dfSCREEN_HEIGHT) {
			RemoveHead();
		}
	}
}

void EnemyHitPlayerCheck() {
	for (int listIndex = 0; listIndex < GetLinkedListSize(); listIndex++) {
		if (LinkedListIndex(listIndex)->bulletX == player.playerX && LinkedListIndex(listIndex)->bulletY == player.playerY) {
			//ĳ���͸� �װ���
			player.liveFlag = false;
			//��带 �����Ͽ� �Ѿ˻���
			RemoveNode(LinkedListIndex(listIndex)->bulletX, LinkedListIndex(listIndex)->bulletY);
			break;
		}
	}
}

void DrawEnemyBullet() {
	for (int listIndex = 0; listIndex < GetLinkedListSize(); listIndex++) {
		Sprite_Draw(LinkedListIndex(listIndex)->bulletX, LinkedListIndex(listIndex)->bulletY, '*');
	}
}



void ShootBullet(int posX, int posY) {
	static int bulletIndex = 0;

	if (bulletIndex == (sizeof(bullet) / sizeof(BULLET)) - 1) {
		bulletIndex = 0;
	}
	

	bullet[bulletIndex].posX = posX;
	bullet[bulletIndex].posY = posY - 1;
	bullet[bulletIndex].shootFlag = true;

	bulletIndex++;
}

void EnemyHitCheck() {
	for (int bulletIndex = 0; bulletIndex < sizeof(bullet) / sizeof(BULLET); bulletIndex++) {
		if (bullet[bulletIndex].posY == 0) {
			bullet[bulletIndex].shootFlag = false;
		}
		for (int enemyIndex = 0; enemyIndex < ENEMYCOUNT; enemyIndex++) {
			if (bullet[bulletIndex].posX == enemy[enemyIndex].posX && bullet[bulletIndex].posY == enemy[enemyIndex].posY && enemy[enemyIndex].liveFlag == true && bullet[bulletIndex].shootFlag == true) {
				enemy[enemyIndex].liveFlag = false;
				bullet[bulletIndex].shootFlag = false;
			}
		}
	}
}

void DrawBullet() {
	for (int bulletIndex = 0; bulletIndex < sizeof(bullet) / sizeof(BULLET); bulletIndex++) {
		if (bullet[bulletIndex].shootFlag == false)
			continue;

		Sprite_Draw(bullet[bulletIndex].posX, bullet[bulletIndex].posY, '^');
		bullet[bulletIndex].posY--;
	}
}
void DrawEnemy() {
	for (int enemyIndex = 0; enemyIndex < ENEMYCOUNT; enemyIndex++) {
		if (enemy[enemyIndex].liveFlag == false) {
			continue;
		}
		Sprite_Draw(enemy[enemyIndex].posX, enemy[enemyIndex].posY, '@');
	}
}

void DrawPlayer() {
	if(player.liveFlag == true)
	Sprite_Draw(player.playerX, player.playerY, 'A');
}

void CheckPlayerWinOrLose()
{
	int checkNum = 0;
	for (int enemyIndex = 0; enemyIndex < ENEMYCOUNT; enemyIndex++) {
		//����� ��� �� �̻� �˻��� �ʿ䰡 �����Ƿ� �ٷ� break�ϰ� ����
		if (enemy[enemyIndex].liveFlag == true) {
			break;
		}
		checkNum++;
	}

	if (checkNum == ENEMYCOUNT) {
		winOrLose = true;
		scene = 4;
	}

	if (player.liveFlag == false) {
		winOrLose = false;
		scene = 4;
	}
}

void Play() {
	
	Buffer_Clear();

	MessageEnQueue();
	EnemyMessageEnQueue();

	
	MessageMovement();
	EnemyMessageMovement();
	EnemyAttack();
	EnemyHitCheck();
	EnemyHitPlayerCheck();
	MoveEnemyBullet();

	DrawEnemyBullet();
	DrawEnemy();
	DrawBullet();
	DrawPlayer();
	Buffer_Flip();
	
	CheckPlayerWinOrLose();
}