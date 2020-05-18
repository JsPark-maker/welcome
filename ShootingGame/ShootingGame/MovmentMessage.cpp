#include <stdio.h>
#include "MovementMessage.h"
#define MAX_QUEUE 6

int cQueue[MAX_QUEUE];

int front = 0;

int rear = 0;

bool EnQueue(int val) {

	if (isFull() == true) 
		return false;
	else {
		rear = ++rear % MAX_QUEUE;
		cQueue[rear] = val;
		return true;
	}
}

bool DeQueue(int* val) {
	if (isEmpty() == true)
		return false;
	else {

		front = ++front % MAX_QUEUE;
		*val = cQueue[front];
		return true;
	}
}

bool isFull() {
	if ((rear + 1) % MAX_QUEUE == front)
		return true;
	else
		return false;
}

bool isEmpty() {
	if (front == rear) 
		return true;
	else
		return false;
}

bool Peek(int* val) {

	if (isEmpty() == true) {
		return false;
	}
	else {
		*val = cQueue[(front + 1) % MAX_QUEUE];
		return true;
	}
}