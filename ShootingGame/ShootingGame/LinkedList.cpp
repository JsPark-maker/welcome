#include "LinkedList.h"

LinkedList linkedList;

void NodeAdd(int X, int Y)
{
    NODE* node = new NODE;
    node->bulletX = X;
    node->bulletY = Y;
    linkedList.size++;

    if (linkedList.head == nullptr) {
        linkedList.head = node;
        linkedList.tail = node;
    }
    else {
        linkedList.tail->next = node;
        linkedList.tail = linkedList.tail->next;
    }
}
void RemoveHead() {
    NODE* ptr = linkedList.head->next;
    delete linkedList.head;
    linkedList.head = ptr;
    linkedList.size--;
}
void RemoveNode(int bulletX, int bulletY)
{
    NODE* ptr = linkedList.head;
    NODE* tmp = ptr;

    while (ptr != nullptr) {
        if (ptr->bulletY == bulletY && ptr->bulletX == bulletX) {
            break;
        }
        else {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if (ptr != nullptr) {
        if (ptr == linkedList.head) {
            linkedList.head = linkedList.head->next; //다음 것을 머리로 만들어줌
        }
        linkedList.size--;
        tmp->next = ptr->next;
        delete ptr;
    }

}
//몇번째에 어떤 노드가있는지 알려줌
NODE* LinkedListIndex(int index)
{
    NODE* ptr = linkedList.head;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    return ptr;
}

int GetLinkedListSize()
{
    return linkedList.size;
}
