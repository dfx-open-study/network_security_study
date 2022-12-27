//링크드 리스트를 이용한 QUEUE 자료구조 구현
//큐의 앞을 가리키는 front 포인터와 back 포인터 지정
//큐에 enqueue 하기 위해 링크드 리스트 노드를 생성하여 queue의 back 포인터에 연결후 back 포인터 이동
//큐에서 dequeue 하기 위해 front에 연결되어 있는 노드를 뽑아내고 다음 노드에 Front 설정
//랜덤한 숫자를 랜덤한 갯수만큼 enqueue하고 랜덤한 갯수만큼 dequeue 하는 코드 작성
//각 enqueue와 dequeue시 queue의 사이즈 출력

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node //노드 정의
{
    int data;
    struct Node *link;
}Node;


typedef struct Queue //Queue 구조체 정의
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
    Node* temp = (Node*)malloc(sizeof(Node)); //노드 생성
    temp->data = data;//데이터 설정
    temp->link = NULL;

    if (IsEmpty(q))//큐가 비어있을 때
    {
        q->front = temp;
        q->rear = temp;
    }
    else//비어있지 않을 때
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
    if (IsEmpty(q))//큐가 비었을 때
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