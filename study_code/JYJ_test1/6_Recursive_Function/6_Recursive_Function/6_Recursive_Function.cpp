#include <stdio.h>
#include <Windows.h>
#define SCREAN_HEIGHT 10
#define SCREAN_WIDTH 20

char Original[SCREAN_HEIGHT][SCREAN_WIDTH] = {
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' ', 'O', 'O', ' ', ' ', 'O', 'O', 'O', 'O', 'O', 'O' },
    { ' ', ' ', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', ' ', 'O' },
    { ' ', ' ', 'O', 'O', 'O', 'O', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },
    { ' ', 'O', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O' },
    { ' ', 'O', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O' },
    { 'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', ' ', ' ', ' ', 'O', 'O' },
    { 'O', ' ', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', ' ', ' ', ' ', 'O', 'O' },
    { 'O', ' ', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', ' ', ' ', ' ', 'O', 'O' },
    { 'O', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', ' ', ' ', ' ', ' ', 'O', 'O' },
    { 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', 'O', ' ', 'O', ' ', ' ', ' ', ' ', 'O', 'O' },
};

char Temp[SCREAN_HEIGHT][SCREAN_WIDTH];
int main()
{
    int y = 0, x = 0;
    void Print_Screan();
    void Find_Way(int, int, char);
    while (1)
    {
        memcpy(Temp, Original, sizeof(Original));
        Print_Screan();											//화면 출력
        Sleep(2000);
        Find_Way(5, 8, '.');										//길찾기
        Sleep(2000);
    }

    return 0;

}

void Print_Screan()
{
    system("cls");   //화면 청소
    int P_y = 0, P_x = 0;
    for (P_y = 0; P_y < 10; P_y++)
    {
        for (P_x = 0; P_x < 20; P_x++)
        {
            printf("%c", Temp[P_y][P_x]);
        }
        printf("\n");
    }
}

void Find_Way(int F_y, int F_x, char c)
{
    int y = F_y;
    int x = F_x;

    Print_Screan();

    //만약 현재 위치에서 우측에 'O' 가 있는 경우 Temp에서 c로 바꾸고 그 위치에서 다시 find_way 재귀한다.
    if (Temp[y][x + 1] == 'O')
    {
        Temp[y][x + 1] = c;
        Find_Way(y, x+1, '.');
    }
    //만약 현재 위치에서 좌측에 'O' 가 있는 경우 Temp에서 c로 바꾸고 그 위치에서 다시 find_way 재귀한다.
    if (Temp[y][x - 1] == 'O')
    {
        Temp[y][x - 1] = c;
        Find_Way(y, x-1, '.');
    }
    //만약 현재 위치에서 위에 'O' 가 있는 경우 Temp에서 c로 바꾸고 그 위치에서 다시 find_way 재귀한다.
    if (Temp[y - 1][x] == 'O')
    {
        Temp[y-1][x] = c;
        Find_Way(y-1, x, '.');
    }
    //만약 현재 위치에서 아래에 'O' 가 있는 경우 Temp에서 c로 바꾸고 그 위치에서 다시 find_way 재귀한다.
    if (Temp[y + 1][x] == 'O')
    {
        Temp[y+1][x] = c;
        Find_Way(y+1, x, '.');
    }
           
    return;
}
