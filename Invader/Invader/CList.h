#pragma once
#include <iostream>
using namespace std;
template <class T>
class CList
{
public:
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};
	//세팅되있는 값을 그냥 가져오기만하는 구조
	class Iterator {
	private:
		Node* node;
	public:
		Iterator(Node* ptr = nullptr) : node(ptr) {};
		
		const Iterator operator++(int) {
			const Iterator old = *this;
			this->node = this->node->next;
			return old;
		};

		Iterator& operator++() {
			this->node = this->node->next;
			return *this;
		};

		const Iterator operator--(int) {
			const Iterator old = *this;
			this->node = this->node->prev;
			return old;
		};

		Iterator& operator--() {
			this->node = this->node->prev;
			return *this;
		};

		bool operator==(Iterator iter) {
			if (this->node == iter.node) {
				return true;
			}
			return false;
		};

		bool operator!=(Iterator iter) {
			if (this->node == iter.node) {
				return false;
			}
			return true;
		};

		T& operator*() {
			return this->node->data;
		};

		Node* operator->() {
			return this->node;
		};

		void operator=(Iterator iter) {
			this->node = iter.node;
		};
	};

public:
	CList():size(0)
	{
		head = &tail;
		tail.data = NULL;
		tail.prev = nullptr;
		tail.next = nullptr;
	};
	~CList() {};
	Iterator Begin() {
		Iterator iter(head);
		return iter;
	};
	Iterator end() {
		Iterator iter(&tail);
		return iter;
	};
	void Push_Front(T data) {
		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = head;
		newNode->prev = nullptr;
		head->prev = newNode;
		head = newNode;
		size++;
	};
	void Push_back(T data) {
		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = &tail;
		newNode->prev = tail.prev;
		if (newNode->prev == nullptr) {
			head = newNode;
		}
		if (tail.prev != nullptr) {
			tail.prev->next = newNode;
		}
		tail.prev = newNode;
		size++;
	};
	//사용불가
	void Pop_Front() {
		if (size == 0) {
			return;
		}
		//T data = head.next->data;
		Node* tmp = head.next;//삭제할 노드
		head.next->next->prev = &head;
		head.next = head.next->next;
		size--;
		delete tmp;
	};
	//사용불가
	void Pop_back() {
		if (size == 0) {
			return;
		}
		//T data = tail.prev->data;
		Node* tmp = tail.prev;
		tail.prev->prev->next = &tail;
		tail.prev = tail.prev->prev;
		size--;
		delete tmp;
	};
	void Clear() {
		for (int i = 0; i < size; i++) {
			Pop_Front();
		}
	};
	int Size() {
		return size;
	};
	bool Empty() {
		if (size == 0) {
			return true;
		}
		return false;
	};
	//erase를 하기위해...
	//Node* operator*();
	Iterator erase(Iterator iter) {
		Iterator ptr(iter->next);
		Node* nPtr = iter->next->prev;
		if (nPtr == head) {
			head = nPtr->next;
			iter->next->prev = nullptr;
		}
		else {
			iter->prev->next = iter->next;
			iter->next->prev = iter->prev;
		}
		
		this->size--;
		delete nPtr;
		return ptr;
	};
	void RemoveData(T data) {

		for (auto iter = this->Begin(); iter != this->end(); ++iter) {
			if (iter->data == data) {
				this->size--;
				erase(iter);
				return;
			}
		}
		return;
	};

	void ShowAll() {
		for (auto i = this->Begin(); i != this->end() ; ++i)
		{
			std::cout << *i << std::endl;
		}
	}

	T& operator[](int index) {
		int _index = index;
		Node* tmp = head;
		while (_index) {
			tmp = tmp->next;
			_index--;
		}
		return tmp->data;
	}
private:
	int size;
	Node* head;
	Node tail;
};

