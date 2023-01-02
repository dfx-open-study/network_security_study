# 8일차 STUDY & TASK
* TASK
    > INSERT 소팅 구현   
    ```cpp
    #include <stdio.h>
    #define MAX 10
    void Insert(int *);
    void Print(int *, int, int);
    int main()
    {
        int Sort[MAX] = { 8, 3, 4, 1, 9, 6, 7, 2, 5, 0 };
        Insert(Sort);
    }

    void Insert(int *data)
    {
        /*코드 작성*/
    }

    void Print(int *data, int num1, int num2)
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
    ```
    > 위 코드를 참고하여 INSERT 소팅 구현   
    > https://gyoogle.dev/blog/algorithm/Insertion%20Sort.html 참고   

[To main](/README.md)