#include <stdio.h>
#define MAX 10
void Insert(int*);
void Print(int*, int, int);
int main()
{
    int Sort[MAX] = { 8, 3, 4, 1, 9, 6, 7, 2, 5, 0 };
    Insert(Sort);
}

void Insert(int* data)
{
    int i, j, key;

    for (i = 1; i < MAX; i++)
    {
        key = *(data + i);
        for (j = i; j >= 0 && *(data + j - 1) > key; j--)
        {
            *(data + j) = *(data + j - 1);
        }
        *(data + j) = key;

        Print(data, i, j);
    }
}

void Print(int* data, int num1, int num2)
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (i == num1 || i == num2)
        {
            printf("[%d] ", data[i]);
        }
        else
        {
            printf(" %d  ", data[i]);
        }
    }
    printf("\n");
}