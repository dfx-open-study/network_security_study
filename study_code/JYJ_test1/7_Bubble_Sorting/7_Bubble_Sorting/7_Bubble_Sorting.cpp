#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 10
void Bouble(int*);
void Print(int*, int);


int main()
{
    int Sort[MAX] = { 8, 3, 4, 1, 9, 6, 7, 2, 5, 0 };

    Bouble(Sort);
    return 0;
}


void Bouble(int* data)
{
    int i, j, temp;
    for (i = 0; i < MAX; i++) 
    {
        for (j = 0; j < MAX-i-1; j++) 
        {
            if (*(data+j) > *(data+j+1))
            {   
                temp = *(data+j);
                *(data+j) = *(data+j+1);
                *(data+j+1) = temp;
                
                Print(data, j);
             }
        }
    }


}

void Print(int* data, int point)
{
    int i;
    for (i = 0; i < point; i++)
    {
        printf("%d ", data[i]);
    }
    printf("[%d] ", data[point]);
    printf("[%d] ", data[point + 1]);
    for (i = point + 2; i < MAX; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}