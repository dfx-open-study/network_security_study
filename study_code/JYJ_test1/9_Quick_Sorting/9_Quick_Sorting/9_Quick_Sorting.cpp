#include <stdio.h>
#define MAX 10
void Quick(int*, int, int);
void Print(int*, int, int);

int main()
{
    int Sort[MAX] = { 8, 3, 4, 1, 9, 6, 7, 2, 5, 0 };

    Quick(Sort, 0, 9);
    printf("\n");
    return 0;
}

void Print(int* data1, int Left, int Right)
{
    int P;
    for (P = 0; P < Left; P++)
        printf(" %d  ", data1[P]);
    printf("[%d] ", data1[Left]);
    for (P = Left + 1; P < Right; P++)
        printf(" %d  ", data1[P]);
    if (Left != Right)
        printf("[%d] ", data1[Right]);
    for (P = Right + 1; P <= MAX - 1; P++)
    {
        printf(" %d  ", data1[P]);
    }
    printf("\n");
    for (P = 0; P < Left; P++)
        printf("    ");
    for (P = Left; P <= Right; P++)
        printf("^^^^");
    for (P = 0; P < MAX - 1; P++)
    {
        printf("    ");
    }
    printf("\n");
}

void Quick(int* data, int Start, int End)
{
    if (Start >= End)
    {
        return;    //���Ұ� 1���� ���
    }

    int pivot = Start;
    int i = Start + 1;  
    int j = End;
    int temp;

    while (i <= j) 
    {
        Print(data, i, j);

        //�����Ͱ� ������������
        while (i <= End && data[i] <= data[pivot])
        {
            i++;
        }
        while (j > Start && data[j] >= data[pivot])
        {
            j--;
        }

        if (i > j) 
        {
            //������
            temp = data[j];
            data[j] = data[pivot];
            data[pivot] = temp;
        }
        else
        {
            //i��°�� j��°�� ����
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }

    //���� ���
    Quick(data, Start, j-1);
    Quick(data, j+1, End);

}