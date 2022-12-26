#include <iostream>
#define INF 987654321
using namespace std;



struct Node {
    int data;
    Node* next;
};

struct LinkedQueue {
    Node* front, * back;
    int len = 0;
    LinkedQueue() {
        front = back = NULL;
    }
    int size() {
        return len;
    }

    bool isEmpty() {
        return len == 0;
    }

    void enqueue(int data) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = data;
        node->next = NULL;
        if (isEmpty()) {
            front = back = node;
        }
        else {
            back->next = node;
            back = back->next;
        }
        len++;
        printf("%d\n", size());
    }

    int dequeue() {

        if (isEmpty()) {
            cout << "Q is empty" << endl;
            return INF;
        }

        Node* delNode = front;
        int ret = delNode->data;
        front = delNode->next;
        free(delNode);
        len--;
        printf("%d\n", size());
        return ret;
    }
};

int main() {

    LinkedQueue q;
    for (int i = 1; i <= 5; i++) {
        q.enqueue(i);
        
    }

    while (!q.isEmpty())
        cout << q.dequeue() << endl;

}