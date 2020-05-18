#pragma once

//--------------------------------------------------------
//링크드리스트 헤더 시작점
//--------------------------------------------------------
struct NODE {
    int bulletX;
    int bulletY;
    struct NODE* next = nullptr;
};

struct LinkedList {
    NODE* head;
    NODE* tail;
    int size = 0;
};

void NodeAdd(int X, int Y);

void RemoveNode(int X, int Y);

NODE* LinkedListIndex(int index);

int GetLinkedListSize();

void RemoveHead();
//--------------------------------------------------------
//링크드리스트 헤더 끝 점
//--------------------------------------------------------
