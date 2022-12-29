# 7일차 STUDY & TASK
* TASK
    > 버블 소팅 구현   
    ```cpp
    #define _CRT_SECURE_NO_WARNINGS
    #include <stdio.h>
    #define MAX 10
    void Bouble(int *);
    void Print(int *, int);


    int main()
    {
        int Sort[MAX] = { 8, 3, 4, 1, 9, 6, 7, 2, 5, 0 };

        Bouble(Sort);
        return 0;
    }


    void Bouble(int *data)
    {
        /*코드 작성*/
    }

    void Print(int *data, int point)
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
    ```
    > 위 코드를 참고하여 버블 소팅 구현   

[To main](/README.md)