#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>

int* Stack;
int Size;
int Top;

void InitStack(int aSize)
{
    Size = aSize;
    Stack = (int*)malloc(Size * sizeof(int));
    Top = -1;
}

void FreeStack()
{
    free(Stack);
}

 void Push(int data)
{
    if (Top < Size - 1) {
        Top++;
        Stack[Top] = data;
        return ;
    }
    else {
        return ;
    }
}

int Pop()
{
    if (Top >= 0) {
        return Stack[Top--];
    }
    else {
        return -1;
    }
}

void main()
{
    InitStack(256);
    Push(rand());
    Push(rand());
    Push(rand());
    Push(rand());
    Push(rand());
    printf("%d\n", Pop());
    printf("%d\n", Pop());
    printf("%d\n", Pop());
    printf("%d\n", Pop());
    printf("%d\n", Pop());
    FreeStack();
}