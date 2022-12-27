//��ũ�� ����Ʈ�� �̿��� QUEUE �ڷᱸ�� ����
//ť�� ���� ����Ű�� front �����Ϳ� back ������ ����
//ť�� enqueue �ϱ� ���� ��ũ�� ����Ʈ ��带 �����Ͽ� queue�� back �����Ϳ� ������ back ������ �̵�
//ť���� dequeue �ϱ� ���� front�� ����Ǿ� �ִ� ��带 �̾Ƴ��� ���� ��忡 Front ����
//������ ���ڸ� ������ ������ŭ enqueue�ϰ� ������ ������ŭ dequeue �ϴ� �ڵ� �ۼ�
//�� enqueue�� dequeue�� queue�� ������ ���

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node //��� ����
{
    int data;
    struct Node *link;
}Node;


typedef struct Queue //Queue ����ü ����
{
    Node *front, *rear;
    int size;
}Queue;

void Init(Queue* q)
{
    q->front = q->rear = NULL;
    q->size = 1;
}

int IsEmpty(Queue* q)
{
    return (q->front == NULL);  
}

void enqueue(Queue* q, int data)
{
    Node* temp = (Node*)malloc(sizeof(Node)); //��� ����
    temp->data = data;//������ ����
    temp->link = NULL;

    if (IsEmpty(q))//ť�� ������� ��
    {
        q->front = temp;
        q->rear = temp;
    }
    else//������� ���� ��
    {
        q->rear->link = temp;
        q->rear = temp;
        q->size++;
    }
}

int dequeue(Queue* q, int* Value)
{
    int data;
    Node *temp;
    if (IsEmpty(q))//ť�� ����� ��
    { 
        q->size = 0;
        return -1;
    }
    else
    {
        temp = q->front;
        data = temp->data;
        q->front = temp->link;

        if (Value == NULL)
            return -2;
            q->rear == NULL;

        free(temp);
        q->size--;
        return 0;
    }
}

void print_queue(Queue* q)
{
    Node* p;
    for (p = q->front; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
    printf("size : %d\n", q->size);
}

int main()
{
    Queue que;
    int TempValue;
    int result;

    Init(&que);

    srand(time(NULL));

    int num1 = rand() % 9;
    int num2 = rand() % 9;
    int i, j;

    for(i=0; i<=num1; i++)
    {
        enqueue(&que, rand() % 101);
        print_queue(&que);
    }

    for (j = 0; j<=num2; j++)
    {
        result = dequeue(&que, &TempValue);
        if (result == 0)
            printf("dequeue value : %d\n", TempValue);
        print_queue(& que);
    }
    return 0;
}