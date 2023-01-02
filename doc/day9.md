# 9일차 STUDY & TASK
* TASK
    > 퀵 소팅 구현   
    ```cpp
    #include <stdio.h>
    #define MAX 10
    void Quick(int *, int, int);
    void Print(int *, int, int);

    int main()
    {
        int Sort[MAX] = { 8, 3, 4, 1, 9, 6, 7, 2, 5, 0 };

        Quick(Sort, 0, 9);
        printf("\n");
        return 0;
    }



    void Print(int *data1, int Left, int Right)
    {
        int P;
        for (P = 0; P < Left; P++)
            printf(" %d  ", data1[P]);
        printf("[%d] ", data1[Left]);
        for (P = Left + 1; P < Right; P++)
            printf(" %d  ", data1[P]);
        if(Left != Right)
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

    void Quick(int *data, int Start, int End)
    {
        /* 코드 작성*/
    }
    ```
    > 위 코드를 참고하여 버블 소팅 구현   

[To main](/README.md)