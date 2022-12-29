#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

template <typename T>
class Node
{
public:
	T value;
	Node* next;

	Node() :value(0), next(nullptr) {};
	~Node() {};
};

template <typename T>
class Queue
{
public:
	Queue() :head(nullptr), tail(nullptr), size(0) {};
	~Queue() {};

	void Enqueue(T _vaule);
	T Dequeue();
	bool empty();

private:
	Node<T>* head;
	Node<T>* tail;
	int size;
};

int main()
{
	srand((unsigned int)time(NULL));
	int i = 0;
	int j = 0;
	int randnum = 0;
	randnum = rand() % 10;

	Queue<int> queue;
	for (i; i < randnum; i++) {
		queue.Enqueue(rand());

	}
	
	for (j; j < randnum; j++) {

		printf( "%d\n ",queue.Dequeue());
		
	}
	return 0;
}

template<typename T>
void Queue<T>::Enqueue(T _vaule)
{
	Node<T>* newNode = new Node<T>;
	newNode->value = _vaule;
	size++;

	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = tail->next;
	}

}

template<typename T>
T Queue<T>::Dequeue()
{
	size--;
	if (empty())
		return -1;
	else
	{
		Node<T>* ptr = head;
		T vaule = head->value;

		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
			delete(head);
		}
		else
		{
			ptr = ptr->next;
			delete(head);
			head = ptr;
		}
		return vaule;
	}
}

template<typename T>
bool Queue<T>::empty()
{
	if (tail == nullptr)
		return true;
	else
		return false;
}