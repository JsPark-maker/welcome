#include <stdio.h>
#include "EnemyMovementMessage.h"
#define MAX_QUEUE 6

int enemyQueue[MAX_QUEUE];

int enemyFront = 0;

int enemyRear = 0;

bool EnemyEnQueue(int val) {

	if (EnemyisFull() == true) 
		return false;
	else {
		enemyRear = ++enemyRear % MAX_QUEUE;
		enemyQueue[enemyRear] = val;
		return true;
	}
}

bool EnemyDeQueue(int* val) {
	if (EnemyisEmpty() == true)
		return false;
	else {

		enemyFront = ++enemyFront % MAX_QUEUE;
		*val = enemyQueue[enemyFront];
		return true;
	}
}

bool EnemyisFull() {
	if ((enemyRear + 1) % MAX_QUEUE == enemyFront)
		return true;
	else
		return false;
}

bool EnemyisEmpty() {
	if (enemyFront == enemyRear)
		return true;
	else
		return false;
}

bool EnemyPeek(int* val) {

	if (EnemyisEmpty() == true) {
		return false;
	}
	else {
		*val = enemyQueue[(enemyFront + 1) % MAX_QUEUE];
		return true;
	}
}