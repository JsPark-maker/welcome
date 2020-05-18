#pragma once

struct BULLET {
	int posX;
	int posY;
	bool shootFlag = false;
};

struct PLAYER {
	int playerX = 40;
	int playerY = 20;
	bool liveFlag = true;
};

void MessageEnQueue();

void MessageMovement();

void EnemyMessageEnQueue();

void EnemyMessageMovement();

void EnemyAttack();

void EnemyShootBullet(int enemyPosX, int enemyPosY);

void MoveEnemyBullet();

void EnemyHitPlayerCheck();

void DrawEnemyBullet();

void EnemyHitCheck();

void DrawBullet();

void DrawEnemy();

void DrawPlayer();

void Play();

void ShootBullet(int posX, int posY);

void EnemyShootBullet(int enemyPosX, int enemyPosY);

void CheckPlayerWinOrLose();